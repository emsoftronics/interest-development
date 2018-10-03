#ifndef __DBUSSERVICE_H__
#define __DBUSSERVICE_H__

#ifndef DBUS_COMPILATION
#define DBUS_COMPILATION /* Cheat and use private stuff */
#endif
#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef __cplusplus
extern "C"
{
#endif

#include <config.h>
#include <dbus/dbus-mainloop.h>
#include <dbus/dbus-internals.h>

#ifdef __cplusplus
}
#endif

//typedef DBusHandlerResult (*PathMessageFunction_t)(DBusConnection *, DBusMessage *, void *);

/* d-bus connection data */
typedef struct
{
    DBusLoop *loop;
    DBusConnection *connection;
} CData;

/* Server data */
typedef struct
{
    DBusLoop *loop;
    DBusServer *server;
} ServerData;


class CDBusService
{
    public:
        CDBusService(const char *p_InterfaceName, DBusObjectPathMessageFunction p_MessageFunction = NULL,
                DBusObjectPathUnregisterFunction p_UnregisterFunction = NULL);
        virtual ~CDBusService();

        int IsValidDbusConnection();
        const char *GetInterFaceName();
        const char *GetServiceObjectPathName();

        dbus_bool_t TestConnectionSetup(DBusLoop *t_pLoop, DBusConnection *t_pConnection);
        void        TestConnectionShutdown(DBusLoop *t_pLoop, DBusConnection *t_pConnection);
        void        TestConnectionDispatchAllMessages(DBusConnection *t_pConnection);
        dbus_bool_t TestConnectionDispatchOneMessage(DBusConnection *t_pConnection);
        dbus_bool_t TestServerSetup(DBusLoop *t_pLoop, DBusServer *t_pServer);
        void        TestServerShutdown(DBusLoop *t_pLoop, DBusServer *t_pServer);

        void SendPrimitiveToInterface(char *t_pInterfaceName, char *t_pMethodName, int t_iType, void *t_pData);
        void SendMethodToInterface(char *t_pInterfaceName, char *t_pMethodName, unsigned char *t_pData, int t_nSize);
        void SendMethodToInterface(char *t_pInterfaceName, char *t_pMethodName,
                int iArgType1, void *pArg1, int iArgType2, void *pArg2);
        dbus_bool_t SendMethodToInterfaceArgs(char *t_pInterfaceName, char *t_pMethodName, const char *t_pData, int t_nSize);
        dbus_bool_t SendMethodToInterfaceNoArgs(char *t_pInterfaceName, char *t_pMethodName);
        void SendSignalToInterface(char *t_pInterfaceName, char *t_pSignalName);
        void RelayMessageToInterface(char *t_pInterfaceName, DBusMessage * pMsg);

    private:
        static void *DbusCallWaitingThread(void *obj);

        static char *GetObjectPathByInterface(const char *t_pInterfaceName);
        static void FreeObjectPathRetrievedByInterface(char *t_ObjPath);

        static dbus_bool_t AddWatch(DBusWatch *t_pWatch, void *t_pData);
        static void RemoveWatch(DBusWatch *t_pWatch, void *t_pData);
        static void ToggleWatch(DBusWatch *t_pWatch, void *t_pData);
        static dbus_bool_t AddTimeout (DBusTimeout *t_pTimeout, void *t_pData);
        static void RemoveTimeout(DBusTimeout *t_pTimeout, void *t_pData);
        static void DispatchStatusFunction(DBusConnection *t_pConnection, DBusDispatchStatus t_NewStatus, void *t_pData);
        static void CDataFree(void *t_pData);
        static CData* CDataNew(DBusLoop *t_pLoop, DBusConnection *t_pConnection);
        static void ServerDataFree(void *t_Data);
        static ServerData* ServerDataNew(DBusLoop *t_pLoop, DBusServer *t_pServer);
        static dbus_bool_t AddServerWatch(DBusWatch *t_pWatch, void *t_pData);
        static void ToggleServerWatch(DBusWatch *t_pWatch, void *t_pData);
        static void RemoveServerWatch(DBusWatch *t_pWatch, void *t_pData);
        static dbus_bool_t AddServerTimeout(DBusTimeout *t_pTimeout, void *t_pData);
        static void RemoveServerTimeout(DBusTimeout *t_pTimeout, void *t_pData);
        static DBusHandlerResult FilterFunction(DBusConnection *t_pConnection, DBusMessage *t_pMessage, void *t_pUserData);
        //        void PathUnregisteredFunction(DBusConnection  *t_pConnection, void *t_pUserData);
        static DBusHandlerResult DefaultPathMessageFunction(DBusConnection *t_pConnection, DBusMessage
                *t_pMessage, void *t_pUserData);


        int DBusServiceManagerInitialize();
        int DBusServiceManagerRun();

    private:
        DBusLoop 		*m_pLoop;
        DBusObjectPathVTable m_pCallbackVtable;
        char		    *m_pMedallionServicePath;
        char		    *m_pMedallionServiceMgrName;

        DBusConnection 	*m_pConnection;
        pthread_t        m_hThread;
};

#endif /* __DBUSSERVICE_H__ */
