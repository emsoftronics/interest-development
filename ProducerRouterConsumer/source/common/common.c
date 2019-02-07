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



#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cutil.h"
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

static pid_t gs_parent_pid = 0;

/* Create log file with PID/EVC/PR/LAUNCH_TIME/RCV_TIME/DELAYED_BY fields */
FILE *create_log_file(char *file_path, const char *header)
{
    FILE *file = NULL;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (!file_path) return NULL;
    file = fopen(file_path, "w");
    if (!file) perror("fopen write");
    else {
        fprintf(file, "%s\n", header);
        fprintf(file, "\nCreated By:\t %d\n", getpid());
        fprintf(file,"Created On:\t%d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1,
        tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fprintf(file, "\n%6s  EVC  PR  %-18s  %12s  %12s", "PID","LAUNCH_TIME", "DATA_LENGTH", "DELAYED_BY");
        fprintf(file, "\n-------------------------------------------------------------------------------\n");
        fflush(file);
    }
    return file;
}

static char * get_formatted_time(struct timeval timestamp, char *bufferwithformat, int size)
{
    time_t nowtime;
    struct tm *nowtm;
    char fbuf[32] = {0};
    if ((!bufferwithformat) || (size <= 0)) return bufferwithformat;
    strncpy(fbuf, bufferwithformat, sizeof(fbuf));
    nowtime = timestamp.tv_sec;
    nowtm = localtime(&nowtime);
    strftime(bufferwithformat, size, fbuf, nowtm);
    return bufferwithformat;
}


static double get_ms_diff_with_current_time(struct timeval timestamp)
{
    struct timeval ctv;
    gettimeofday(&ctv, NULL);

    return  (double)((ctv.tv_sec - timestamp.tv_sec)*1000
        +  (double)(ctv.tv_usec - timestamp.tv_usec)/1000.0f);

}

static char *get_current_time(const char *format)
{
    static char lbuf[32] = {0};
    struct timeval tv;
    gettimeofday(&tv, NULL);
    strncpy(lbuf, format, sizeof(lbuf));
    return get_formatted_time(tv, lbuf, sizeof(lbuf));
}

/* Dump data packet to log file with PID/EVC/PR/LAUNCH_TIME/RCV_TIME/DELAYED_BY field values */
void ev_pack_dump_to_file(FILE *file, evpack_t *packet)
{
    char buf[32] =  "%d-%m-%y, %H:%M:%S";
    if ((!file) || (!packet)) return;
    fprintf(file, "\n%6d  %3d  %2d  %18s  %6d bytes  %9.4lf ms\n", packet->pid, packet->code,
        packet->priority, get_formatted_time(packet->timestamp, buf, sizeof(buf)),
        packet->datalen, get_ms_diff_with_current_time(packet->timestamp));
    fflush(file);
}

/* Priority compare handler for linklist sorting */
static int compare_handler(void *pack1, void *pack2)
{
    evpack_t *p1 = pack1;
    evpack_t *p2 = pack2;
    if ((!p1) || (!p2)) return 0;
    if (p1->priority > p2->priority) return 1;
    else if (p1->priority <= p2->priority) return -1;
    return 0;
}

/* Initialize context object */
int init_context(context_t *ctx)
{
    if (!ctx) return -1;
    ctx->cfd = -1;
    ctx->pfd = -1;
    ctx->code   =  0;
    ctx->start_timestamp = get_millisecond_time();
    ctx->packet_recieved = 0;
    ctx->logfile = NULL;
    //pthread_t thread;
    ctx->packet_list = sll_createList(SORTED_BY_DCF, compare_handler);
    if (pthread_cond_init(&ctx->condition, NULL) != 0) goto pthread_cond_error;
    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) goto pthread_cond_error;
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0) goto pthread_mutex_error;
    if (pthread_mutex_init( &ctx->lock, &attr) != 0) goto pthread_mutex_error;
    pthread_mutexattr_destroy(&attr);

    return 0;
pthread_mutex_error:
    pthread_mutexattr_destroy(&attr);
    pthread_cond_destroy(&ctx->condition);
pthread_cond_error:
    sll_destroyList(ctx->packet_list);
    ctx->packet_list = NULL;
    return -1;
}

/* Deinitialize context object */
void exit_context(context_t *ctx)
{
    if (!ctx) return;
    if (ctx->cfd > 0) close(ctx->cfd);
    ctx->cfd = -1;
    if (ctx->pfd > 0) close(ctx->pfd);
    ctx->pfd = -1;
    ctx->code = 0;
    ctx->start_timestamp = 0;
    ctx->packet_recieved = 0;
    pthread_cond_destroy(&ctx->condition);
    pthread_mutex_destroy(&ctx->lock);
    if (ctx->packet_list) sll_destroyList(ctx->packet_list);
    ctx->packet_list = NULL;
    if (ctx->logfile) fclose(ctx->logfile);
    ctx->logfile = NULL;
}

/* Allocate and initialize context object */
context_t *create_context(void)
{
    context_t *ctx = (context_t *)malloc(sizeof(context_t));
    if (!ctx) {
        perror("create_context:malloc");
        return NULL;
    }
    if (init_context(ctx) < 0) {
        free(ctx);
        return NULL;
    }

    return ctx;
}

/* Deinitialize and free the the allocated context */
void destroy_context(context_t *ctx)
{
    if (!ctx) return;
    exit_context(ctx);
    free(ctx);
}

/* Create thread with context */
int create_thread(context_t *ctx, thread_handler_t hndlr)
{
    pthread_attr_t tattr;

    if (!ctx) return -1;
    if (pthread_attr_init(&tattr) != 0) goto pthread_attr_error;
    if (pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED) != 0) goto pthread_error;
    if (pthread_create(&ctx->thread, &tattr, hndlr, ctx) != 0) goto pthread_error;
    pthread_attr_destroy(&tattr);
    return 0;
pthread_error:
    pthread_attr_destroy(&tattr);
pthread_attr_error:
    return -1;
}

/* Signal handler */
static void sig_handler (int sig) {
    switch (sig) {
        case SIGQUIT:
        case SIGINT:
        case SIGKILL:
            if (gs_parent_pid != getpid()) _exit(0);
            else {
                kill(-gs_parent_pid, SIGQUIT);
                usleep(10000);
                _exit(0);
            }
            break;
    }
}

/* Enable auto killing of children if parent process is killed */
void enable_auto_kill_childs(void)
{
    gs_parent_pid = getpid();
    if (signal(SIGQUIT, sig_handler)==SIG_ERR) printf("SIGQUIT: Unable to register\n");
    if (signal(SIGINT, sig_handler)==SIG_ERR) printf("SIGINT: Unable to register\n");
}

/* Wait until all childrens are terminated */
void wait_for_all_childs_termination(void)
{
    int status;
    while(wait(&status) > 0);
}

/*Left trim the string if specified chars are available at left end of string */
char *ltrim(char *str, char *tchrs)
{
    char *p = str;
    char *q = tchrs;
    if ((!str) || (!tchrs)) return str;
    while((*p) && (*q)){
        q = tchrs;
        while(*q) {
            if (*q == *p) {p++; break;}
            else q++;
        }
    }
    if (p != str) {
        q = p; p = str;
        while(*q) {*p = *q; p++; q++;}
        *p = '\0';
    }
    return str;
}

/*Right trim the string if specified chars are available at right end of string */
char *rtrim(char *str, char *tchrs)
{
    char *p = NULL;
    char *q = tchrs;
    if ((!str) || (!tchrs)) return str;
    p = str + strlen(str) - 1;
    while((p >= str) && (*q)){
        q = tchrs;
        while(*q) {
            if (*q == *p) {p--; break;}
            else q++;
        }
    }
    *(++p) = '\0';
    return str;
}

int get_full_data_packet(int fd, evpack_t **p, int timeout)
{
    int len = 0;
    if (!p) return -1;
    if (*p) free(*p);
    *p = (evpack_t *)malloc(sizeof(evpack_t));
    if(!(*p)) return -1;
    if (watch_fd(fd, timeout) > 0) {
        if (read(fd, *p, sizeof(evpack_t) - 1) < sizeof(evpack_t) - 1) goto connection_error;
        if ((*p)->datalen > 1) {
            len = sizeof(evpack_t) + (*p)->datalen - 1;
            *p = (evpack_t *)realloc(*p, len);
            if (!(*p)) return -1;
            len = read(fd, (*p)->payload, (*p)->datalen);
            if(len <= 0) goto connection_error;
            len += sizeof(evpack_t) - 1;
        }
        else len = sizeof(evpack_t);
        return len;
    }
connection_error:
    if(*p)free(*p);
    *p = NULL;
    return -1;
}
