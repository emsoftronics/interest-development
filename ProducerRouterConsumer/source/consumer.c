/*
 * =====================================================================================
 *
 *       Filename:  consumer.c
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cutil.h"

static char gs_router[32] = "router";
static int gs_consumers =  2;
static char gs_log_dir_path[128] = "/tmp";
//static int gs_msdelay = 10;
static context_t gs_context = {0};

static void parse_arg(int argc, char **argv)
{
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, ":r:c:p:h")) != -1)
    {
        switch(opt)
        {
            case 'h':  printf("Usage: %s [option] [arg]\n", argv[0]);
                printf("-h              Help.\n");
                printf("-r <router>     Router service name. default : %s.\n", gs_router);
                printf("-c <consumers>  Number of consumers need to be use (default: %d).\n", gs_consumers);
                printf("-p <dir_path>   Directory for received packet logs (default: %s).\n", gs_log_dir_path);
                //printf("-d <interval>   Event generation interval (in ms)(default: %d ms).\n", gs_msdelay);
                exit(0);
                break;
            case 'r':
                strcpy(gs_router, optarg);
                break;
            case 'p':
                strcpy(gs_log_dir_path, optarg);
                break;
            case 'c':
                gs_consumers = atoi(optarg);
                break;
                /*
            case 'd':
                gs_msdelay = atoi(optarg);
                if (gs_msdelay < 1) gs_msdelay = 1;
                break;
                */
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

static void handle_packet(evpack_t *pack, context_t *ctx)
{
    ev_pack_dump_to_file(ctx->logfile, pack, 1);
}

static void create_consumer(int code)
{
    evpack_t packet = {0, code, 0xfff, 0};
    rtrim(gs_log_dir_path, "/ ");
    if (!is_accessible_dir(gs_log_dir_path)) {
        strcat(gs_log_dir_path, "_C");
        mkdir(gs_log_dir_path, 0777);
    }
    strcat(gs_log_dir_path, "/consumer");
    mkdir(gs_log_dir_path, 0777);
    if(is_accessible_dir(gs_log_dir_path)) {
        char str[32];
        snprintf(str, sizeof(str), "/logfile-%d", code);
        strcat(gs_log_dir_path, str);
        gs_context.logfile = create_log_file(gs_log_dir_path, "\t\tConsumer Logs\n\t\t===============\n");
    }

    while(1) {
        gs_context.cfd = connect_to_server(gs_router, -1);
        if (send_data(gs_context.cfd, &packet, sizeof(evpack_t)) < sizeof(evpack_t)) {
            close(gs_context.cfd);
            gs_context.cfd = -1;
        }

        if (gs_context.cfd > 0) {
            while(check_connection_termination(gs_context.cfd) <= 0) {
                if (read(gs_context.cfd, &packet, sizeof(evpack_t)) < sizeof(evpack_t)) break;
                handle_packet(&packet, &gs_context);
            }
            close(gs_context.cfd);
        }
    }
}

static int create_consumer_process(int code)
{
    pid_t pid = fork();
    switch(pid) {
        case 0:
            create_consumer(code);
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

    for (i = 1; i <= gs_consumers; i++) create_consumer_process(i);

    wait_for_all_childs_termination();
    return 0;
}
