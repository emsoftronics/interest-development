
#include "vmcutil.h"
#include "cutil.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_WAITTIME_FOR_CONNECTION_RETRY 100

#ifdef DEFAULT_CLIENT_CONTEXT
#define DCC_CAT(_x) gs_ ## _x
#define GS_VAR_DCC(_x)  DCC_CAT(_x)
#define DCC_GS_VAR  GS_VAR_DCC(DEFAULT_CLIENT_CONTEXT)
static ccontext_t DCC_GS_VAR = {
    .sockfd = -1,
    .smemfd = -1,
    .lockinitdone = 1,
    .locked = 0,
    .smemsize = 0,
    .lock = PTHREAD_MUTEX_INITIALIZER,
};

ccontext_t *def_client(void) { return &DCC_GS_VAR;}
#endif

static int init_server_side_client_context(ccontext_t *ctx);
static void reset_context(ccontext_t *ctx);
static int lock_context(ccontext_t *ctx);
static void unlock_context(ccontext_t *ctx);

static int init_client_context(ccontext_t *ctx, const char *servername, unsigned long sizeofsmem)
{
    if ((!ctx) || (!servername) || (sizeofsmem == 0)) return -1;

    if ((ctx->sockfd = connect_to_server(servername, MAX_WAITTIME_FOR_CONNECTION_RETRY)) <= 0)
        goto init_failure;

    ctx->smemsize = sizeofsmem;
    if ((ctx->smemfd = alloc_shared_mem(sizeofsmem, &(ctx->smemref))) <= 0) goto init_failure;

    if (!(ctx->lockinitdone)) {
        pthread_mutexattr_t  mta;
        if (pthread_mutexattr_init(&mta) < 0) goto init_failure;

        /* or PTHREAD_MUTEX_RECURSIVE_NP */
        if (pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE) < 0) {
            pthread_mutexattr_destroy(&mta);
            goto init_failure;
        }

        if (pthread_mutex_init(&(ctx->lock), &mta)  < 0) {
            pthread_mutexattr_destroy(&mta);
            goto init_failure;
        }
        pthread_mutexattr_destroy(&mta);
        ctx->lockinitdone = 1;
        ctx->locked = 0;
    }
    ctx->frame.vid.pid = (int)getpid();
    ctx->frame.vid.rid = get_rnd_no(0x8ffffff,0xfffffff);
    return 0;
init_failure:
    reset_context(ctx);
    return -1;
}

static int init_server_side_client_context(ccontext_t *ctx)
{
    if ((!ctx) || (ctx->sockfd <= 2)) return -1;
    //clear_rx_buffer(ctx->sockfd);
    ctx->smemfd = rcv_fd(ctx->sockfd);
    if (ctx->smemfd <= 2) goto init_failure;

    ctx->smemsize = ctx->frame.size;
    if ((long)ctx->smemsize <= 0) goto init_failure;

    ctx->smemref = map_smem(ctx->smemfd, ctx->smemsize);
    if (ctx->smemref == NULL) goto init_failure;
#ifdef ENABLE_MUTEX_FOR_SERVER_CLIENT_CONTEXT
    if (!(ctx->lockinitdone)) {
        pthread_mutexattr_t  mta;
        if (pthread_mutexattr_init(&mta) < 0) goto init_failure;

        /* or PTHREAD_MUTEX_RECURSIVE_NP */
        if (pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE) < 0) {
            pthread_mutexattr_destroy(&mta);
            goto init_failure;
        }

        if (pthread_mutex_init(&(ctx->lock), &mta)  < 0) {
            pthread_mutexattr_destroy(&mta);
            goto init_failure;
        }
        pthread_mutexattr_destroy(&mta);
        ctx->lockinitdone = 1;
        ctx->locked = 0;
    }
#else
    ctx->lockinitdone = 0;
#endif
    return 0;
init_failure:
    reset_context(ctx);
    return -1;
}

static void reset_context(ccontext_t *ctx)
{
    if (!ctx) return;
    if (ctx->sockfd > 2) {
        shutdown(ctx->sockfd, SHUT_RDWR);
        close(ctx->sockfd);
    }
    ctx->sockfd = -1;
    if (ctx->smemfd > 2) close(ctx->smemfd);
    ctx->smemfd = -1;
    if (ctx->smemref) unmap_smem(ctx->smemref, ctx->smemsize);
    ctx->smemref = NULL;
    ctx->smemsize = 0;
    ctx->frame.vid.pid = 0;
    ctx->frame.vid.rid = 0;
    ctx->frame.qid = ctx->frame.offset = 0;
    ctx->frame.size = 0;
    if (ctx->lockinitdone) {
        while (ctx->locked) unlock_context(ctx);
    }
    if (ctx->lockinitdone == 2) {
        pthread_mutex_destroy(&(ctx->lock));
        ctx->lockinitdone = 0;
    }
}

static int send_call(ccontext_t *ctx)
{
   qframe_t lframe = {0};
   if ((ctx->sockfd <= 2) || (ctx->smemfd <= 2)) return -1;
   ctx->frame.qid = get_rnd_no(1,0x7f);
   ctx->frame.offset = 0;
   ctx->frame.size = ctx->smemsize;
   if (check_connection_termination(ctx->sockfd) > 0) goto ErrorToReset;
   clear_rx_buffer(ctx->sockfd);
   if (send_data(ctx->sockfd, &(ctx->frame), sizeof(qframe_t)) != sizeof(qframe_t))
       goto ErrorToReset;
   lframe.qid = -2;
   while (lframe.qid == -2) {
       lframe.qid = 0;
       if (wait_for_response(ctx->sockfd, 500, &lframe, sizeof(lframe)) < 0) goto ErrorToReset;
       if ((lframe.vid.pid == ctx->frame.vid.pid) && (lframe.vid.rid == ctx->frame.vid.rid)) {
           if (lframe.qid == -2) {
               clear_rx_buffer(ctx->sockfd);
               if (send_fd(ctx->sockfd, ctx->smemfd) < 0)
                   goto ErrorToReset;
           }
           else if (lframe.qid != ctx->frame.qid) return -1;
       }
       else return -1;
   }

   ctx->frame.offset = lframe.offset;
   ctx->frame.size = lframe.size;

   return 0;
ErrorToReset:
   reset_context(ctx);
   return -1;
}

static int rcv_call(ccontext_t *ctx)
{
    uint32_t qid = 0;
    fcall_hdr_t *call_hdr = NULL;
    if (ctx->sockfd <= 2) return -1;

    if (wait_for_response(ctx->sockfd, -1, &(ctx->frame), sizeof(qframe_t)) < 0) goto ErrorToReset;
    if (ctx->smemfd <= 2) {
        qid = ctx->frame.qid;
        ctx->frame.qid = -2;
        clear_rx_buffer(ctx->sockfd);
        if (send_data(ctx->sockfd, &(ctx->frame), sizeof(qframe_t)) < sizeof(qframe_t)) goto ErrorToReset;
        ctx->frame.qid = qid;
        if (init_server_side_client_context(ctx) < 0) return -1;
    }

    ctx->smemfd = resize_shared_mem(ctx->smemfd, ctx->smemsize, ctx->frame.size, &(ctx->smemref));
    if (ctx->smemfd < 0)  goto ErrorToReset;
    else ctx->smemsize = ctx->frame.size;

    call_hdr = ctx->smemref;
    if ((ctx->frame.vid.pid != call_hdr->vid.pid) || (ctx->frame.vid.rid != call_hdr->vid.rid))
        goto ErrorToReset;

    return 0;
ErrorToReset:
   reset_context(ctx);
   return -1;
}
#if 0
static inline void *get_arg_ptr(ccontext_t *ctx, int index)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    return (fhdr->arg[index].type)
        ? ((char *)fhdr) + *((uint32_t *)(((char *)fhdr)+fhdr->arg[index].offset))
        : ((char *)fhdr)+fhdr->arg[index].offset;
}
#endif
static inline void *get_ret_ptr(ccontext_t *ctx)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    return (((char *)fhdr) + fhdr->endoff);
}


void handle_ipc_calls(int cfd, ipc_fcall_t fcall_handler)
{
    ccontext_t context = {0};
    context.sockfd = cfd;
    while(watch_fd(context.sockfd, -1) > 0) {
        if (rcv_call(&context) == 0) {
                int argc = CHARGC((&context));
                int fid = METHODID((&context));
                void *args[argc];
                int *ret = get_ret_ptr(&context);
                int i;
                for (i = 0; i < argc; i++) args[i] = get_arg_ptr(&context, i);

                SMEM_WRITE_LOCK((&context));
                if (fcall_handler)
                    fcall_handler(fid, argc, args, ret, &(context.frame.size));
                SMEM_WRITE_UNLOCK((&context));
                context.frame.offset = (unsigned long)ret - (unsigned long)(context.smemref);
                clear_rx_buffer(context.sockfd);
                if (send_data(context.sockfd, &context.frame, sizeof(qframe_t)) < (int)sizeof(qframe_t)) break;
        }
        else break;
    }
    reset_context(&context);
}


static int lock_context(ccontext_t *ctx)
{
    if (!ctx) return -1;
    if (ctx->lockinitdone) {
        pthread_mutex_lock(&(ctx->lock));
        ctx->locked++;
    }
    else return -1;
    return 0;
}

static void unlock_context(ccontext_t *ctx)
{
    if (!ctx) return;
    if (ctx->lockinitdone && (ctx->locked > 0)) {
        ctx->locked--;
        pthread_mutex_unlock(&(ctx->lock));
    }
}

ccontext_t *get_client_context(ccontext_t *ctx, const char *servername, int argc, unsigned long total_arg_mem)
{
    unsigned long pagesize = 512;
    unsigned long smemsize  = sizeof(fcall_hdr_t) + argc*sizeof(datamem_t)
                                        + total_arg_mem + 4*sizeof(void *);
    int lockinitflag = 0;
    if (!ctx) return NULL;
    if (ctx->lockinitdone) {
        if (lock_context(ctx) < 0) return NULL;
        lockinitflag = 1;
    }
#ifdef USE_GETPAGESIZE
    pagesize = (unsigned long)getpagesize();
#elif defined USE_SYSCONF_PAGE
    pagesize = (unsigned long)sysconf(_SC_PAGESIZE);
#else
#ifdef USE_PAGE_1K
    pagesize = 1<<10;
#endif
#ifdef USE_PAGE_2K
    pagesize = 1<<11;
#endif
#ifdef USE_PAGE_4K
    pagesize = 1<<12;
#endif
#endif
    smemsize = ALIGN_BY_SIZE(smemsize, pagesize);

    if ((ctx->sockfd <= 2)||(ctx->smemfd <= 2)) {
        if (init_client_context(ctx, servername, smemsize) < 0) {
            //printf("client context initialization error!!\n");
            return NULL;
        }
    }

    if (!lockinitflag) {
        if (lock_context(ctx) < 0) return NULL;
    }

    ctx->smemfd = resize_shared_mem(ctx->smemfd, ctx->smemsize, smemsize, &(ctx->smemref));
    if (ctx->smemfd < 0) {
        reset_context(ctx);
        return NULL;
    }
    else ctx->smemsize = smemsize;

    SMEM_WRITE_LOCK(ctx);
    return ctx;
}

void *call_function(ccontext_t *ctx)
{
    SMEM_WRITE_UNLOCK(ctx);
    if (send_call(ctx) == 0) return get_ret_ptr(ctx);
    return NULL;
}

void release_client_context(ccontext_t *ctx)
{
    unsigned long pagesize = 512;
    if ((!ctx) || (ctx->smemfd < 2)) return;
#ifdef USE_GETPAGESIZE
    pagesize = (unsigned long)getpagesize();
#elif defined USE_SYSCONF_PAGE
    pagesize = (unsigned long)sysconf(_SC_PAGESIZE);
#else
#ifdef USE_PAGE_1K
    pagesize = 1<<10;
#endif
#ifdef USE_PAGE_2K
    pagesize = 1<<11;
#endif
#ifdef USE_PAGE_4K
    pagesize = 1<<12;
#endif
#endif
    ctx->smemfd = resize_shared_mem(ctx->smemfd, ctx->smemsize, pagesize, &(ctx->smemref));
    if (ctx->smemfd < 0) {
        reset_context(ctx);
        return;
    }
    else ctx->smemsize = pagesize;
    unlock_context(ctx);
}

void *get_arg_ptr(ccontext_t *ctx, int index)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    void *arg_ptr = ((char *)fhdr)+fhdr->arg[index].offset;
    if (fhdr->arg[index].type) {
        if (fhdr->arg[index].type == 2)  {
            void **ptr = (void **) (((char *)fhdr) + *((uint32_t *)arg_ptr));
            int i = 0;
            for(i = 0; ptr[i] != NULL; i++) {
                ptr[i] = (void *)(((char *)fhdr)+(uint32_t)ptr[i]);
            }
                fhdr->arg[index].type = 1;
            return ptr;
        }
        else {
            if (*((uint32_t *)arg_ptr) < (unsigned long)(fhdr->arg)-(unsigned long)fhdr
                + (fhdr->argc * sizeof(datamem_t))-1)
                return (void *)(*((uint32_t *)arg_ptr));
            else return ((char *)fhdr) + *((uint32_t *)arg_ptr);
        }
    }

    return arg_ptr;
}

