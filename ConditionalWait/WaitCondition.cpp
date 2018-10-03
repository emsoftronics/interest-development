/*
 * =====================================================================================
 *
 *       Filename:  WaitCondition.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 14 February 2018 12:41:44  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#include "WaitCondition.h"
//#include "Mutex.h"
#include <time.h>
#include <stdio.h>
#include<cstdlib>
#include <unistd.h>
//#include<iostream>
using namespace std;
CWaitCondition::CWaitCondition():m_Cond(PTHREAD_COND_INITIALIZER),m_bPredicate(false)
{

}

CWaitCondition::~CWaitCondition()
{
    pthread_cond_destroy(&m_Cond);
}

int CWaitCondition::Wait(pthread_mutex_t& mutex, unsigned long timeToWait )
{
    int nRet = 0;
    if (timeToWait == ULONG_MAX)
    {
        while(!m_bPredicate)
            nRet = pthread_cond_wait(&m_Cond, &mutex);
        m_bPredicate = false;
    }
    else
    {
        struct timespec time_to_wait;
        time_to_wait.tv_sec = time(NULL) + timeToWait;
        while(!m_bPredicate)
            nRet = pthread_cond_timedwait(&m_Cond, &mutex, &time_to_wait) ;
        m_bPredicate = false;
    }
    return ((nRet == SIGNALLED || nRet == TIMED_OUT) ? nRet : INVALID);
}

int CWaitCondition::Signal()
{
    m_bPredicate = true;
    return pthread_cond_signal(&m_Cond);
}
int CWaitCondition::Broadcast()
{
    m_bPredicate = true;
    return pthread_cond_broadcast(&m_Cond);
}
