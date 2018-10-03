#include "DBusService.h"
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <semaphore.h>
#include <error.h>
#include <string.h>
#include <pthread.h>
#define MAX_TRY 20
#define CHANGE_CLIENT_BY(_x) do{clientInterface[11] = 0x30+(_x);}while(0)

static char gSignal[] = "s0";
static char gMethod[] = "f0";
static char serverInterface[64];
static char clientInterface[] = "test.client0.interface";
static struct timespec requestedTime;
static char tmpBuff[128];
static sem_t responseWaitLock;
static pthread_mutex_t mutexLock;

static void GetCurrentTime(struct timespec *spec)
{
    clock_gettime(CLOCK_MONOTONIC, spec);
}

static long GetElapsedTimeSince(struct timespec *lastTime)
{
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_MONOTONIC, &spec);
    s = spec.tv_sec - lastTime->tv_sec;
    ms = (spec.tv_nsec - lastTime->tv_nsec)/1000000L;
    ms += (s*1000L);
    return ms;
}

static char *GetStr(char c, unsigned int count)
{
    int i = 0;
    for ( i = 0; i < (int)count; i++) tmpBuff[i] = c;
    tmpBuff[count] = '\0';
    return tmpBuff;
}

static void InitClient(void)
{
    GetStr('-',30);
    printf("\n+-%s-+--%s---+--------+\n", tmpBuff, tmpBuff);
    printf("| %-30s | %33s | %6s |\n+-%s-+--%s---+--------+\n",
            "Requesting Client","Requested Method with server",
            "E-Time", tmpBuff, tmpBuff);
    GetCurrentTime(&requestedTime);

    if (sem_init(&responseWaitLock, 0, 0) == -1)
        syslog(LOG_DEBUG,"sem_init : %s", strerror(errno));

    pthread_mutex_init(&mutexLock, NULL);
}

static void WaitForResponse(int timeout)
{
    int semOut = 0;
    struct timespec ts;

    /* Calculate relative interval as current time plus number of seconds given atimeout */
    ts.tv_sec = time(NULL) + timeout;
    ts.tv_nsec = 0;

    if (timeout < 0) {
        if (sem_wait(&responseWaitLock) < 0) {
            syslog(LOG_DEBUG, "sem_wait: %s", strerror(errno));
        }
    }
    else {
        semOut = sem_timedwait(&responseWaitLock, &ts);
        if (semOut < 0) {
            if (errno == ETIMEDOUT) syslog(LOG_DEBUG, "Response waiting is Timed out");
            else syslog(LOG_DEBUG, "sem_timedwait: %s", strerror(errno));
        }
    }
}

static void NotifyResponseReceived(void)
{
    int semVal = 0;
    pthread_mutex_lock(&mutexLock);
    sem_getvalue(&responseWaitLock, &semVal);
    if (semVal <= 0) {
        if (sem_post(&responseWaitLock) == -1) syslog(LOG_DEBUG,"Error: sem_post failed!!");
    }
    pthread_mutex_unlock(&mutexLock);
}

static DBusHandlerResult PathMessageFunction(DBusConnection *t_pConnection, DBusMessage *t_pMessage, void *t_pUserData)
{
    DBusHandlerResult dbResult = DBUS_HANDLER_RESULT_HANDLED;
    DBusError dbError;
    CDBusService *dbusServiceObj = (CDBusService *)t_pUserData;

    dbus_error_init(&dbError);
    syslog(LOG_DEBUG, "%s: Reply recieved.",dbusServiceObj->GetInterFaceName());
    if (dbus_message_is_signal(t_pMessage, dbusServiceObj->GetInterFaceName(), gSignal))
    {
        syslog(LOG_DEBUG, "%s: Function Call completed!",gMethod);
        printf(/*syslog(LOG_DEBUG,*/ "| %-30s | %30s.%s | %6ld |\n+-%s-+--%s---+--------+\n",
                dbusServiceObj->GetInterFaceName(),serverInterface, gMethod,
                GetElapsedTimeSince(&requestedTime), tmpBuff, tmpBuff);
        NotifyResponseReceived();
    }

    return dbResult;
}

void CallMethod(CDBusService *cdbus)
{
    static int method = 1;

    if ((method == 0) || (method > 3))
        method = 1;
    while(!cdbus->IsValidDbusConnection())usleep(500000);
    gMethod[1] = 0x30 + method;
    gSignal[1] = 0x30 + method;
    GetCurrentTime(&requestedTime);
    cdbus->SendMethodToInterface(serverInterface, gMethod,(unsigned char *)clientInterface, strlen(clientInterface)+1);
    WaitForResponse(20);
    method++;
}

void CallMethod2(CDBusService *cdbus)
{
    while(!cdbus->IsValidDbusConnection())usleep(500000);
    cdbus->SendMethodToInterface(serverInterface, "f0",(unsigned char *)clientInterface, strlen(clientInterface)+1);
    //usleep(50000);
}

int main(int argc, char **argv)
{
    pid_t pid = -1;
    int counter = 0;
    int client_no = 0;
    int server_index = 0;
    CDBusService *clientCdbus = NULL;
    if (argc == 1) {
        printf("Atleast on serverInterface is required as input argument.\n");
    }

    InitClient();
    pid = fork();
    switch(pid) {
        case 0:
            pid = fork();
            switch(pid) {
                case 0: client_no = 4;
                    break;
                case -1:
                    break;
                default: client_no = 2;
            }
            break;
        case -1:
            break;
        default:
            pid = fork();
            switch(pid) {
                case 0: client_no = 3;
                    break;
                case -1:
                    break;
                default: client_no = 1;
            }
    }

    CHANGE_CLIENT_BY(client_no);
    clientCdbus = new CDBusService(clientInterface, PathMessageFunction);

    server_index = client_no%(argc-1) + 1;
    memcpy(serverInterface, argv[server_index], strlen(argv[server_index])+1);

    while(counter++ < MAX_TRY) {
        if (client_no % 2) CallMethod(clientCdbus);
        else CallMethod2(clientCdbus);
    }

    delete clientCdbus;
    return 0;
}
