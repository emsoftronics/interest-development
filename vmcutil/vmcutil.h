
#ifndef __VMCUTIL_H__
#define __VMCUTIL_H__
#include <pthread.h>
#include <stdint.h>

#define CHARGC    ((fcall_hdr_t *)(_ctx->smemref))->argc
#define CHARGS    ((fcall_hdr_t *)(_ctx->smemref))->arg

#define START_FCALL(_ctx, _func) void *__tmp[10] = {NULL};int _tloop, _argoff; \
              ((fcall_hdr_t *)(_ctx->smemref))->vid = ctx->frame.vid; \
              ((fcall_hdr_t *)(_ctx->smemref))->size = ctx->smemsize; \
              ((fcall_hdr_t *)(_ctx->smemref))->swlocked = 0;         \
              ((fcall_hdr_t *)(_ctx->smemref))->methodid = _func;     \
              CHARGC =0;

#define ADD_FCALL_ARG(_ctx, _arg, _type)  CHARGS[CHARGC].offset =      \
    (CHARGC)? CHARGS[CHARGC-1].offset + CHARGS[CHARGC -1].length : 0;  \
    CHARGS[CHARGC].length = sizeof(_arg); CHARGS[CHARGC].type = _type; \
    __tmp[CHARGC] = (void *)&(_arg); CHARGC++;


#define END_FCALL(_ctx)  _argoff = \
                   (int)((fcall_hdr_t *)(0))->arg + CHARGC * sizeof(datamem_t); \
                   for(_tloop = 0; _tloop < (int)CHARGC; _tloop++) {  \
                       CHARGS[_tloop].offset += _argoff;                \
                       memcpy((char*)(_ctx->smemref) + CHARGS[_tloop].offset, \
                       __tmp[_tloop], CHARGS[_tloop].length);               \
                   }                                    \
                   _tloop = _CHARGS[CHARGC - 1].offset + CHARGS[CHARGC - 1].length;


#define UPDATE_PARG_MEM(_ctx, _arg, _size, _aindex) _argoff = _tloop;       \
                      _tloop += _size;                           \
                       memcpy((char*)(_ctx->smemref) + CHARGS[_aindex].offset, \
                       &_argoff, sizeof(void*));               \
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
    datamem_t arg[1];
} fcall_hdr_t ;

extern int init_client_context(ccontext_t *ctx, const char *servername, unsigned long sizeofsmem);
extern int init_server_side_client_context(ccontext_t *ctx);
extern void reset_context(ccontext_t *ctx);
extern int send_call(ccontext_t *ctx);
extern int rcv_call(ccontext_t *ctx);


static inline void *get_arg(ccontext_t *ctx, int index)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    return (fhdr->arg[index].type)
        ? ((char *)fhdr) + *((long *)(((char *)fhdr)+fhdr->arg[index].offset))
        : ((char *)fhdr)+fhdr->arg[index].offset;
}

#ifdef __cplusplus
}
#endif

#endif
