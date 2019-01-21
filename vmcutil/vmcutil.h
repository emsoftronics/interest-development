
#ifndef __VMCUTIL_H__
#define __VMCUTIL_H__
#include <pthread.h>
#include <stdint.h>

#define CHARGC(_ctx)    ((fcall_hdr_t *)(_ctx->smemref))->argc
#define CHARGS(_ctx)    ((fcall_hdr_t *)(_ctx->smemref))->arg

#define START_FCALL(_ctx, _func) void *tmp[10] = {NULL}; int _tloop, _argoff; \
              ((fcall_hdr_t *)(_ctx->smemref))->vid = _ctx->frame.vid; \
              ((fcall_hdr_t *)(_ctx->smemref))->size = _ctx->smemsize; \
              ((fcall_hdr_t *)(_ctx->smemref))->swlocked = 0;         \
              ((fcall_hdr_t *)(_ctx->smemref))->methodid = _func;     \
              CHARGC(_ctx) = 0;

#define ADD_FCALL_ARG(_ctx, _arg, _type)  CHARGS(_ctx)[CHARGC(_ctx)].offset =      \
    (CHARGC(_ctx))? CHARGS(_ctx)[CHARGC(_ctx)-1].offset + CHARGS(_ctx)[CHARGC(_ctx) -1].length : 0;  \
    CHARGS(_ctx)[CHARGC(_ctx)].length = sizeof(_arg); CHARGS(_ctx)[CHARGC(_ctx)].type = _type; \
    tmp[CHARGC(_ctx)] = (void *)&(_arg); CHARGC(_ctx)++;


#define END_FCALL(_ctx)  _argoff = \
                   (long)(((fcall_hdr_t *)(0))->arg) + CHARGC(_ctx) * sizeof(datamem_t); \
                   for(_tloop = 0; _tloop < (int)CHARGC(_ctx); _tloop++) {  \
                       CHARGS(_ctx)[_tloop].offset += _argoff;                \
                       memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_tloop].offset, \
                       tmp[_tloop], CHARGS(_ctx)[_tloop].length);               \
                   }                                    \
                   ((fcall_hdr_t *)(_ctx->smemref))->endoff = \
                   CHARGS(_ctx)[CHARGC(_ctx) - 1].offset + CHARGS(_ctx)[CHARGC(_ctx) - 1].length;


#define UPDATE_PARG_MEM(_ctx, _arg, _size, _aindex) _argoff = ((fcall_hdr_t *)(_ctx->smemref))->endoff; \
                       ((fcall_hdr_t *)(_ctx->smemref))->endoff += _size;           \
                       memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_aindex].offset, \
                       &_argoff, sizeof(void *));               \
                       memcpy((char*)(_ctx->smemref) + _argoff, (void *)_arg, _size);



#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute__((packed)) vid{
    uint32_t pid;
    uint32_t rid;
} vid_t;

typedef struct __attribute__((packed)) qframe{
    vid_t vid;
    int32_t qid:8;
    int32_t offset:24;
    uint32_t size;
} qframe_t;

typedef struct __attribute__((packed)) ccontext{
    int sockfd;
    int smemfd;
    qframe_t frame;
    uint32_t smemsize;
    void *smemref;
    pthread_mutex_t lock;
} ccontext_t;

typedef struct __attribute__((packed)) datamem{
    uint32_t offset;
    uint32_t length:24;
    uint32_t type:8;
} datamem_t;

typedef struct __attribute__((packed)) fcall_hdr{
    vid_t vid;
    uint32_t size;
    uint16_t methodid;
    uint8_t swlocked;
    uint8_t argc;
    uint32_t endoff;
    datamem_t arg[1];
} fcall_hdr_t ;

extern int init_client_context(ccontext_t *ctx, const char *servername, unsigned long sizeofsmem);
extern int init_server_side_client_context(ccontext_t *ctx);
extern void reset_context(ccontext_t *ctx);
extern int send_call(ccontext_t *ctx);
extern int rcv_call(ccontext_t *ctx);


static inline void *get_arg_ptr(ccontext_t *ctx, int index)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    printf("%d : %d\n", fhdr->arg[index].offset, *((uint32_t *)(((char *)fhdr)+fhdr->arg[index].offset)));
    return (fhdr->arg[index].type)
        ? ((char *)fhdr) + *((uint32_t *)(((char *)fhdr)+fhdr->arg[index].offset))
        : ((char *)fhdr)+fhdr->arg[index].offset;
}

static inline void *get_ret_ptr(ccontext_t *ctx)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    return (((char *)fhdr) + fhdr->endoff);
}

#ifdef __cplusplus
}
#endif

#endif
