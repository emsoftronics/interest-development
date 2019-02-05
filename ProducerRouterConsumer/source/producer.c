/*
 * =====================================================================================
 *
 *       Filename:  producer.c
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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cutil.h"

static char gs_router[32] = "router";
static int gs_producers =  2;
static char gs_log_dir_path[128] = "/tmp";
static int gs_msdelay = 10;
static context_t gs_context = {0};

static void parse_arg(int argc, char **argv)
{
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, ":r:c:p:d:h")) != -1)
    {
        switch(opt)
        {
            case 'h':  printf("Usage: %s [option] [arg]\n", argv[0]);
                printf("-h              Help.\n");
                printf("-r <router>     Router service name. default : %s.\n", gs_router);
                printf("-c <producers>  Number of producers need to be use (default: %d).\n", gs_producers);
                printf("-p <dir_path>   Directory for request logs (default: %s).\n", gs_log_dir_path);
                printf("-d <interval>   Event generation interval (in ms)(default: %d ms).\n", gs_msdelay);
                exit(0);
                break;
            case 'r':
                strcpy(gs_router, optarg);
                break;
            case 'p':
                strcpy(gs_log_dir_path, optarg);
                break;
            case 'c':
                gs_producers = atoi(optarg);
                break;
            case 'd':
                gs_msdelay = atoi(optarg);
                if (gs_msdelay < 1) gs_msdelay = 1;
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

/* Fill the transmission packet  */
static void fill_packet(evpack_t *p, context_t *ctx)
{
    if ((!p) || (!ctx)) return;
    p->pid = getpid();
    p->code = ctx->code;
    p->priority = get_rnd_no(1, 10);
    gettimeofday(&(p->timestamp), NULL);
    ev_pack_dump_to_file(ctx->logfile, p, 0);
}

/* Fill the transmission packet  */
static void create_producer(int code)
{
    evpack_t packet = {0, code, 10, 0.0f};
    rtrim(gs_log_dir_path, "/ ");
    if (!is_accessible_dir(gs_log_dir_path)) {
        strcat(gs_log_dir_path, "_P");
        mkdir(gs_log_dir_path, 0777);
    }
    strcat(gs_log_dir_path, "/producer");
    mkdir(gs_log_dir_path, 0777);
    if(is_accessible_dir(gs_log_dir_path)) {
        char str[32];
        snprintf(str, sizeof(str), "/logfile-%d", code);
        strcat(gs_log_dir_path, str);
        gs_context.logfile = create_log_file(gs_log_dir_path, "\t\tProducer Logs\n\t\t=============\n");
    }

    gs_context.code = code;
    fill_packet(&packet, &gs_context);
    while(1) {
        gs_context.cfd = connect_to_server(gs_router, -1);
        if (gs_context.cfd > 0) {
            while(check_connection_termination(gs_context.cfd) <= 0) {
                if (send_data(gs_context.cfd, &packet, sizeof(evpack_t)) < 0) break;
                usleep(gs_msdelay*1000);
                fill_packet(&packet, &gs_context);
            }
            close(gs_context.cfd);
        }
    }
}

static int create_producer_process(int code)
{
    pid_t pid = fork();
    switch(pid) {
        case 0:
            create_producer(code);
            exit(EXIT_SUCCESS);
            break;
        case -1: return -1;
        default: return pid;
    }
    return 0;
}

int main (int argc, char **argv)
{
    int i;

    enable_auto_kill_childs();
    parse_arg(argc, argv);
    if (init_context(&gs_context) < 0) return -1;

    for (i = 1; i <= gs_producers; i++) create_producer_process(i);

    wait_for_all_childs_termination();
    return 0;
}
