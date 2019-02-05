/*
 * =====================================================================================
 *
 *       Filename:  router.c
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
#include <string.h>
#include <stdlib.h>
#include "linklist.h"
#include "cutil.h"
#include <unistd.h>
#include <sys/socket.h>

static char gs_router[32] = "router";
//static int gs_producers =  2;
//static char gs_log_dir_path[128] = "/tmp";
//static char *gs_log_path = NULL;
static int gs_list_size = 100;
//static context_t gs_context = {0};

static slist_ref_t gs_context_list = NULL;


static pthread_mutex_t gs_lock = PTHREAD_MUTEX_INITIALIZER;

static void parse_arg(int argc, char **argv)
{
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, ":r:l:h")) != -1)
    {
        switch(opt)
        {
            case 'h':  printf("Usage: %s [option] [arg]\n", argv[0]);
                printf("-h              Help.\n");
                printf("-r <router>     Router service name. default : %s.\n", gs_router);
                //printf("-c <producers>  Number of producers need to be use (default: %d).\n", gs_producers);
                //printf("-p <dir_path>   Directory for request logs (default: %s).\n", gs_log_path);
                printf("-l <max_limit>  Even request link list storage max. limit(default: %d).\n", gs_list_size);
                exit(0);
                break;
            case 'r':
                strcpy(gs_router, optarg);
                break;
                /*
            case 'p':
                strcpy(gs_log_dir_path, optarg);
                gs_log_path = (strlen(gs_log_dir_path) > 0) ? gs_log_dir_path : NULL;
                break;
            case 'c':
                gs_producers = atoi(optarg);
                break;
                */
            case 'l':
                gs_list_size = atoi(optarg);
                if (gs_list_size < 1) gs_list_size = 1;
                break;
            case ':':
                printf("option needs a value!\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }
    // optind is for the extra arguments
    // which are not parsed
    /*
    for(; optind < argc; optind++){
        printf(“extra arguments: %s\n”, argv[optind]);
    }
    */

}


context_t *get_context(slist_ref_t list ,int code)
{
    context_t *tmp = NULL;
    if (!list) return NULL;
    for (tmp = sll_getListItem(ITEM_BEGIN, list, 0, 0); tmp != NULL;
        tmp = sll_getListItem(ITEM_NEXT, list, 0, 0)) {
        if (tmp->code == code ) return tmp;
    }
    return NULL;
}

static void *consumer_thread(void *arg)
{
    context_t *ctx = arg;
    evpack_t packet = {0};

    if (!ctx) return NULL;
    while(check_connection_termination(ctx->cfd) <= 0) {
        if (sll_getListItemCount(ctx->packet_list) > 0) {
            if (sll_removeFromHead(ctx->packet_list, &packet, NULL)
                < sizeof(evpack_t)) break;
            if (send_data(ctx->cfd, &packet, sizeof(evpack_t)) < sizeof(evpack_t)) {
                sll_addAtHead(ctx->packet_list, &packet, sizeof(evpack_t), 0);
                break;
            }
        }
        else {
            pthread_mutex_lock(&(ctx->lock));
            pthread_cond_wait(&(ctx->condition), &(ctx->lock));
            pthread_mutex_unlock(&(ctx->lock));
        }
    }

    shutdown(ctx->cfd, SHUT_RDWR);
    close (ctx->cfd);
    return NULL;
}

static void *producer_thread(void *arg)
{
    context_t *ctx = arg;
    evpack_t packet = {0};

    if (!ctx) return NULL;
    while(check_connection_termination(ctx->pfd) == 0) {
        if (read(ctx->pfd, &packet, sizeof(evpack_t)) < sizeof(evpack_t)) break;
        if (packet.code == ctx->code) {
            if (sll_getListItemCount(ctx->packet_list) <= gs_list_size) {
                sll_addToList(ctx->packet_list, &packet, sizeof(evpack_t), 0);
            }
            else {
                pthread_mutex_lock(&gs_lock);
                printf("\nServer list storage is overflowed and droping packet: ");
                ev_pack_dump_to_file(stdout, &packet, 1);
                pthread_mutex_unlock(&gs_lock);
            }
        }
        pthread_mutex_lock(&(ctx->lock));
        pthread_cond_signal(&(ctx->condition));
        pthread_mutex_unlock(&(ctx->lock));
    }

    shutdown(ctx->pfd, SHUT_RDWR);
    close (ctx->pfd);
    return NULL;
}

static int create_client_thread(int fd, evpack_t *pack)
{
    context_t *ctx = NULL;
    if ((fd <= 2) || (!pack)) return -1;

    if (!gs_context_list) gs_context_list = sll_createList(SORTED_NONE, NULL);

    ctx = get_context(gs_context_list, pack->code);
    if (!ctx) {
            ctx = create_context();
            ctx->code = pack->code;
            sll_addAtTail(gs_context_list, ctx, sizeof(context_t), 0);
            //destroy_context(ctx);
            free(ctx);
            ctx = get_context(gs_context_list, pack->code);
    }

    if (pack->priority >= (uint16_t)0xff) {
        ctx->cfd = fd;
        create_thread(ctx, consumer_thread);
    }
    else {
        ctx->pfd = fd;
        sll_addToList(ctx->packet_list, pack, sizeof(evpack_t), 0);
        create_thread(ctx, producer_thread);
    }
    return 0;
}

static void handle_client_context(int fd)
{
    evpack_t packet = {0};
    if (check_connection_termination(fd) > 0) goto connection_error;
    if (read(fd, &packet, sizeof(evpack_t)) < sizeof(evpack_t)) goto connection_error;
    if (create_client_thread(fd, &packet) < 0) goto connection_error;
    return;
connection_error:
    if (fd > 2) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}

int main(int argc, char **argv)
{
    int serversock = -1, cfd;
    parse_arg(argc, argv);

    serversock = make_local_server(gs_router);
    if (serversock <= 2) return -1;
    while(1) {
        cfd = wait_for_client(serversock, -1);
        if (cfd > 0) handle_client_context(cfd);
    }
    return 0;
}

