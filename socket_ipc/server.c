/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 26 June 2017 12:40:03  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "sipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern void client_demo(void);


void *server_thread( void * value)
{
    if (sipc_startServer(DEFAULT_SOCKET_PATH) < 0) {
        printf("Starting of server is failed!!\n");
    }
    pthread_exit(value);
}


int main()
{
    int res,err;
    pthread_attr_t attr;
    pthread_t thread1;

    res = pthread_attr_init(&attr);
    if (res != 0) {
        perror("Attribute init failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("Setting detached state failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread1, &attr, server_thread, NULL);
    if (res != 0) {
        perror("Creation of thread failed");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    client_demo();

    pthread_attr_destroy(&attr);
    return 0;
}
