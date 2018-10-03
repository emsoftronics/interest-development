/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 14 February 2018 01:02:15  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "WaitCondition.h"
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
CWaitCondition cond;
void * thread(void *arg)
{
    long d = (long)((char *)arg);
    pthread_mutex_lock(&mutex);
    if (cond.Wait(mutex, d) == CWaitCondition::TIMED_OUT) {
        printf("Thread-%d is timed out.\n", pthread_self());
    }
    else {
        printf("Thread-%d is signaled.\n", pthread_self());
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(void)
{
    int i = 0;
    pthread_t pid[10];

    for ( i = 0; i < 10 ; i++) pthread_create(&pid[i],NULL, thread, (void *)((i+1)*3));
    sleep(2);
    printf("signal to the threads\n");
    cond.Signal();
    sleep(9);
    printf("BroadCast to the threads\n");
    cond.Broadcast();
    for ( i = 0; i < 10 ; i++) pthread_join(pid[i], NULL);
    return 0;
}
