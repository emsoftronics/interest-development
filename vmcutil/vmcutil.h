
#ifndef __VMCUTIL_H__
#define __VMCUTIL_H__
#include <pthread.h>
#include <stdint.h>

#define CHARGC(_ctx)    ((fcall_hdr_t *)(_ctx->smemref))->argc
#define CHARGS(_ctx)    ((fcall_hdr_t *)(_ctx->smemref))->arg
#define METHODID(_ctx)  ((fcall_hdr_t *)(_ctx->smemref))->methodid
#define CHARG_OFFSET(_ctx)  ((long)(((fcall_hdr_t *)(0))->arg) + CHARGC(_ctx) * sizeof(datamem_t))


#define SMEM_WRITE_LOCK(_ctx) ({\
                        while(((fcall_hdr_t *)(_ctx->smemref))->swlocked) usleep(500); \
                        ((fcall_hdr_t *)(_ctx->smemref))->swlocked = 1;})

#define SMEM_WRITE_UNLOCK(_ctx) ({((fcall_hdr_t *)(_ctx->smemref))->swlocked = 0;})

#define START_FCALL(_ctx, _func) void *tmp[12] = {NULL}; long _tloop, _argoff; \
              ((fcall_hdr_t *)(_ctx->smemref))->vid = _ctx->frame.vid;        \
              ((fcall_hdr_t *)(_ctx->smemref))->size = _ctx->smemsize;        \
              ((fcall_hdr_t *)(_ctx->smemref))->swlocked = 0;                 \
              ((fcall_hdr_t *)(_ctx->smemref))->methodid = _func;             \
              CHARGC(_ctx) = 0;

#define ADD_FCALL_ARG(_ctx, _arg, _type)  CHARGS(_ctx)[CHARGC(_ctx)].offset =      \
                        (CHARGC(_ctx))? CHARGS(_ctx)[CHARGC(_ctx)-1].offset        \
                                    + CHARGS(_ctx)[CHARGC(_ctx) -1].length : 0;    \
                        CHARGS(_ctx)[CHARGC(_ctx)].length = sizeof(_arg);          \
                        CHARGS(_ctx)[CHARGC(_ctx)].type = _type;                   \
                        tmp[CHARGC(_ctx)] = (void *)&(_arg); CHARGC(_ctx)++;


#define END_FCALL(_ctx)  _argoff = CHARG_OFFSET(_ctx);                                   \
                   for(_tloop = 0; _tloop < (int)CHARGC(_ctx); _tloop++) {               \
                       CHARGS(_ctx)[_tloop].offset += _argoff;                           \
                       memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_tloop].offset,      \
                       tmp[_tloop], CHARGS(_ctx)[_tloop].length); }                      \
                   ((fcall_hdr_t *)(_ctx->smemref))->endoff =                            \
                        CHARGS(_ctx)[CHARGC(_ctx) - 1].offset                            \
                            + CHARGS(_ctx)[CHARGC(_ctx) - 1].length;


#define UPDATE_PARG_MEM(_ctx, _arg, _size, _aindex) _argoff =                           \
                       ((fcall_hdr_t *)(_ctx->smemref))->endoff;                        \
                       if ((long)(_arg) < CHARG_OFFSET(_ctx)) {                         \
                       memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_aindex].offset,    \
                        &(_arg), sizeof(void *));                                       \
                       } else {                                                         \
                       memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_aindex].offset,    \
                       &_argoff, sizeof(void *));                                       \
                       memcpy((char*)(_ctx->smemref) + _argoff, (void *)_arg, _size);   \
                       ((fcall_hdr_t *)(_ctx->smemref))->endoff += _size; }

#define UPDATE_ARRAY_OF_MEM(_ctx, _arg, _count, _lenptr, _aindex)                       \
                       _argoff =  ((fcall_hdr_t *)(_ctx->smemref))->endoff;             \
                       ((fcall_hdr_t *)(_ctx->smemref))->endoff += (_count)*sizeof(void*); \
                       if ((long)(_arg) < CHARG_OFFSET(_ctx)) {                         \
                        memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_aindex].offset,   \
                            &(_arg), sizeof(void *));                                   \
                       } else {                                                         \
                            void **ptr = (void **) ((char*)(_ctx->smemref) + _argoff);  \
                            int _len = 0;                                               \
                            CHARGS(_ctx)[_aindex].length = (_count) * sizeof(void*);    \
                            memcpy((char*)(_ctx->smemref) + CHARGS(_ctx)[_aindex].offset,\
                            &_argoff, sizeof(void *));                                  \
                            for (_tloop = 0; _tloop < (_count); _tloop++) {             \
                                _len = ((long)(_lenptr) > 0) ? _lenptr[_tloop]          \
                                : strlen(_arg[_tloop]) + 1;                             \
                                _argoff =  ((fcall_hdr_t *)(_ctx->smemref))->endoff;    \
                                memcpy((char*)(_ctx->smemref) + _argoff,                \
                                (void *)_arg[_tloop], _len);  ptr[_tloop] = _argoff;    \
                                ((fcall_hdr_t *)(_ctx->smemref))->endoff += _len; }}

#ifdef __cplusplus
extern "C" {
#endif


typedef void (*ipc_fcall_t) (int, int, void **, void*, uint32_t *);

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
    uint16_t lockinitdone;
    uint16_t locked;
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

extern void handle_ipc_calls(int cfd, ipc_fcall_t fcall_handler);
extern ccontext_t *get_client_context(ccontext_t *ctx, const char *servername, int argc, unsigned long total_arg_mem);
extern void *call_function(ccontext_t *ctx);
extern void release_client_context(ccontext_t *ctx);

static inline void *get_arg_ptr(ccontext_t *ctx, int index)
{
    fcall_hdr_t *fhdr = ctx->smemref;
    void *arg_ptr = ((char *)fhdr)+fhdr->arg[index].offset;
    if (fhdr->arg[index].type) {
        if (*((int32_t *)arg_ptr) < (long)(fhdr->arg)-(long)fhdr
                + (fhdr->argc * sizeof(datamem_t))-1)
            return (void *)(*((long *)arg_ptr));
        else return ((char *)fhdr) + *((uint32_t *)arg_ptr);
    }

    return arg_ptr;
}

#ifdef DEFAULT_CLIENT_CONTEXT
#define DCC_QUOTE(name) #name
#define DCC_STR(macro) DCC_QUOTE(macro)
#define DCC_SERVER  DCC_STR(DEFAULT_CLIENT_CONTEXT)
extern ccontext_t *def_client(void);
#define DCC_Ctx def_client()
#define DCC_START_CALL(_fid, _argc, _extramem)  do { int largc = (_argc);               \
                        ccontext_t *_ctx = get_client_context(DCC_Ctx,                  \
                        DCC_SERVER , largc, (_extramem));                               \
                        if (!_ctx) break;                                               \
                        START_FCALL(_ctx, (_fid))  while(0)

#define DCC_ADD_ARG(_arg, _type)    ADD_FCALL_ARG(_ctx, _arg, _type) while(0)

#define DCC_ARG_OVER()  END_FCALL(_ctx) while(0)

#define DCC_ADD_APTR_MEM(_arg, _size, _aindex)                                          \
                        UPDATE_PARG_MEM(_ctx, _arg, (_size), (_aindex)) while(0)

#define DCC_UPDATE_NON_CONST_PTR_ON_RET(_dstptr, _size, _aindex)                        \
                        if ((long)(_dstptr) > CHARG_OFFSET(_ctx))                       \
                        memcpy((void *)(_dstptr), get_arg_ptr(_ctx, _aindex), _size)

#define DCC_RET_VAL(_retvar) _retvar = *((typeof(_retvar) *)call_function(_ctx))

#define DCC_RET_ONLY()  call_function(_ctx)

#define DCC_END_CALL()  release_client_context(_ctx); } while(0)
#endif


#define RUN_FCALL_SERVER(_server, _fchndlr) ({int _sockfd,  _cfd;               \
                        _sockfd = make_local_server((const char *)(_server));   \
                        while(1) { _cfd = wait_for_client(_sockfd, -1);         \
                        handle_ipc_calls(_cfd, _fchndlr);}                      \
                        close(_sockfd); })

#ifdef DEFAULT_FCALL_SERVER
#define DFS_QUOTE(name) #name
#define DFS_STR(macro) DFS_QUOTE(macro)
#define DFS_SERVER  DFS_STR(DEFAULT_FCALL_SERVER)
#define RUN_DEFAULT_FCALL_SERVER(_fchndlr) RUN_FCALL_SERVER(DFS_SERVER, _fchndlr)
#endif

#ifdef __cplusplus
}
#endif

#endif
