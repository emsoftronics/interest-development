/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 01 February 2019 12:50:10  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), jagdish.prajapati@ltts.com
 *        Company:  L&T Technology & Services
 *
 * =====================================================================================
 */



#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdio.h>
#include "linklist.h"
#include <pthread.h>
#include <sys/time.h>

typedef struct __attribute__((packed)) evpack{
    uint32_t pid;
    uint16_t code;
    uint16_t priority;
    struct timeval timestamp;
} evpack_t;

typedef struct {
    int pfd;
    int cfd;
    int code;
    long double start_timestamp;
    long long packet_recieved;
    FILE *logfile;
    pthread_mutex_t lock;
    pthread_t thread;
    pthread_cond_t condition;
    slist_ref_t packet_list;
} context_t;

typedef void *(*thread_handler_t)(void *);

extern FILE *create_log_file(char *file_path, const char *header);
extern void ev_pack_dump_to_file(FILE *file, evpack_t *packet, int enable_rx_time);

extern int init_context(context_t *ctx);
extern void exit_context(context_t *ctx);
extern context_t *create_context(void);
extern void destroy_context(context_t *ctx);
extern int create_thread(context_t *ctx, thread_handler_t hndlr);
extern void enable_auto_kill_childs(void);
extern void wait_for_all_childs_termination(void);
extern char *ltrim(char *str, char *tchrs);
extern char *rtrim(char *str, char *tchrs);
#endif /* __COMMON_H__ */
