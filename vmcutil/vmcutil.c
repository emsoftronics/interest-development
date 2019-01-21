
#include "vmcutil.h"
#include "cutil.h"
#include <sys/socket.h>

int init_client_context(ccontext_t *ctx, const char *servername, unsigned long sizeofsmem)
{
    pthread_mutexattr_t  mta;
    if ((!ctx) || (!servername) || (sizeofsmem == 0)) return -1;
    reset_context(ctx);
    if ((ctx->sockfd = connect_to_server(servername, 100)) <= 0) goto init_failure;

    ctx->smemsize = sizeofsmem;
    if ((ctx->smemfd = alloc_shared_mem(sizeofsmem, &(ctx->smemref))) <= 0) goto init_failure;

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
    ctx->frame.vid.pid = (int)getpid();
    ctx->frame.vid.rid = get_rnd_no(0x8ffffff,0xfffffff);
    return 0;
init_failure:
    reset_context(ctx);
    return -1;
}

int init_server_side_client_context(ccontext_t *ctx)
{
    int len = sizeof (qframe_t);
    pthread_mutexattr_t  mta;
    if ((!ctx) || (ctx->sockfd <= 2)) return -1;
    clear_rx_buffer(ctx->sockfd);

    printf("waiting for fd\n"); //Log
    ctx->smemfd = rcv_fd(ctx->sockfd);
    if (ctx->smemfd <= 2) goto init_failure;

    printf("recieved fd with size : %d\n", ctx->frame.size); //Log
    ctx->smemsize = ctx->frame.size;
    if ((long)ctx->smemsize <= 0) goto init_failure;
    printf("%s: %d\n", __func__, __LINE__);
    ctx->smemref = map_smem(ctx->smemfd, ctx->smemsize);
    if (ctx->smemref == NULL) goto init_failure;

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
    printf("%s: %d\n", __func__, __LINE__);
    return 0;
init_failure:
    reset_context(ctx);
    return -1;
}

void reset_context(ccontext_t *ctx)
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
    pthread_mutex_destroy(&(ctx->lock));
    ctx->frame.vid.pid = 0;
    ctx->frame.vid.rid = 0;
    ctx->frame.qid = ctx->frame.offset = 0;
    ctx->frame.size = 0;
}

int send_call(ccontext_t *ctx)
{
   qframe_t lframe = {0};
   if ((ctx->sockfd <= 2) || (ctx->smemfd <= 2)) return -1;
   ctx->frame.qid = get_rnd_no(1,0x7f);
   ctx->frame.offset = 0;
   ctx->frame.size = ctx->smemsize;
   clear_rx_buffer(ctx->sockfd);
    printf("sent request\n"); //Log
   if (send_data(ctx->sockfd, &(ctx->frame), sizeof(qframe_t)) != sizeof(qframe_t))
       goto ErrorToReset;
   lframe.qid = -2;
   while (lframe.qid == -2) {
       lframe.qid = 0;
       if (wait_for_response(ctx->sockfd, 500, &lframe, sizeof(lframe)) < 0) goto ErrorToReset;
       printf("Recieved, qid = %d, offset = %d, size = %d\n", lframe.qid, lframe.offset, lframe.size); //Log added
       if ((lframe.vid.pid == ctx->frame.vid.pid) && (lframe.vid.rid == ctx->frame.vid.rid)) {
           if (lframe.qid == -2) {
               clear_rx_buffer(ctx->sockfd);
               printf("sent fd\n"); //Log
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

int rcv_call(ccontext_t *ctx)
{
    uint32_t qid = 0;
    fcall_hdr_t *call_hdr = NULL;
    if (ctx->sockfd <= 2) return -1;

    if (wait_for_response(ctx->sockfd, -1, &(ctx->frame), sizeof(qframe_t)) < 0) goto ErrorToReset;
       printf("Recieved, qid = %d, offset = %d, size = %d\n", ctx->frame.qid, ctx->frame.offset, ctx->frame.size); //Log added
    if (ctx->smemfd <= 2) {
        qid = ctx->frame.qid;
        ctx->frame.qid = -2;
        clear_rx_buffer(ctx->sockfd);
        printf("sent response\n"); //Log
        if (send_data(ctx->sockfd, &(ctx->frame), sizeof(qframe_t)) < sizeof(qframe_t)) goto ErrorToReset;
        ctx->frame.qid = qid;
        if (init_server_side_client_context(ctx) < 0) return -1;
    }

    printf("%s: %d\n", __func__, __LINE__);
    call_hdr = ctx->smemref;
    if ((ctx->frame.vid.pid != call_hdr->vid.pid) || (ctx->frame.vid.rid != call_hdr->vid.rid))
        goto ErrorToReset;

    printf("%s: %d\n", __func__, __LINE__);
    return 0;
ErrorToReset:
   reset_context(ctx);
   return -1;
}



