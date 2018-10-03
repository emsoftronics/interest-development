/**
 * @file DBusService.cpp
 * @brief This file contains the functions to handle incoming messages to servicemanager
 *		and to send method/signal calls to other modules.
 * @author Medallion and LTTS
 * @version 1.0
 *****************************************************************************/
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dbus/dbus.h>
#include <syslog.h>
#include <linux/ioctl.h>
#include "DBusService.h"

#ifndef LOG_TAG
#define LOG_TAG "DBusTest"
#endif



void *CDBusService::DbusCallWaitingThread(void *obj)
{
    int flag = 0;
    CDBusService *cDbusServiceRef = NULL;
    if (obj == NULL ) pthread_exit(NULL);
    cDbusServiceRef = (CDBusService *)obj;
    //Setting the dbus session bus address. dbus socket is opened during the bootup
    setenv("DBUS_SESSION_BUS_ADDRESS","unix:path=/dev/socket/dbus",1);
    syslog(LOG_DEBUG, "%s: Thread started", cDbusServiceRef->m_pMedallionServiceMgrName);
    do {
        if (cDbusServiceRef->DBusServiceManagerInitialize() >= 0) {
            syslog(LOG_DEBUG, "%s: Initialized Successfully.", cDbusServiceRef->m_pMedallionServiceMgrName);
            flag = cDbusServiceRef->DBusServiceManagerRun();
        }
        else {
            syslog(LOG_DEBUG, "%s: Initialization failed.", cDbusServiceRef->m_pMedallionServiceMgrName);
        }
    } while(flag);
    syslog(LOG_DEBUG, "%s: Thread exited", cDbusServiceRef->m_pMedallionServiceMgrName);
    pthread_exit(NULL);
}

char *CDBusService::GetObjectPathByInterface(const char *t_pInterfaceName)
{
    char *objPath = NULL;
    int interfaceLen = 0;

    if (t_pInterfaceName != NULL) {
        interfaceLen = strlen(t_pInterfaceName);
        objPath = new char [interfaceLen+2];

        if (objPath) {
            memset(objPath, 0 , interfaceLen+2);
            objPath[0] = '/';
            memcpy(objPath+1, t_pInterfaceName, interfaceLen+1);
            char *ltmp = NULL;
            char *ctmp = objPath+1;
            while (*ctmp)
            {
                if(*ctmp == '.') {*ctmp = '/';ltmp = ctmp;}
                ctmp++;
            }
            if (ltmp) *ltmp = '\0';
            //syslog(LOG_DEBUG, "DBUS_OBJ_PATH: %s", m_pMedallionServicePath);
        }
    }
     return objPath;
}

void CDBusService::FreeObjectPathRetrievedByInterface(char *t_ObjPath)
{
    if (t_ObjPath) {
        delete t_ObjPath;
    }
}


CDBusService::CDBusService(const char *p_InterfaceName, DBusObjectPathMessageFunction p_MessageFunction,
        DBusObjectPathUnregisterFunction p_UnregisterFunction)
{
    int interfaceLen = 0;

    m_pLoop = NULL;
    m_pMedallionServiceMgrName = NULL;
    m_pMedallionServicePath = NULL;
    m_pConnection = NULL;
    memset((void *)&m_pCallbackVtable,0,sizeof(m_pCallbackVtable));
    m_pCallbackVtable.unregister_function = p_UnregisterFunction;
    if (p_MessageFunction == NULL) {
        m_pCallbackVtable.message_function = DefaultPathMessageFunction;
    }
    else {
        m_pCallbackVtable.message_function = p_MessageFunction;
    }

    if (p_InterfaceName != NULL) {
        interfaceLen = strlen(p_InterfaceName);
        m_pMedallionServiceMgrName = new char [interfaceLen+1];
        if (m_pMedallionServiceMgrName) {
            memcpy(m_pMedallionServiceMgrName, p_InterfaceName, interfaceLen+1);
            syslog(LOG_DEBUG, "DBUS_Interface: %s", m_pMedallionServiceMgrName);
        }

        m_pMedallionServicePath = GetObjectPathByInterface(p_InterfaceName);
#if 0
        if (m_pMedallionServicePath) {
            memset(m_pMedallionServicePath, 0 , interfaceLen+2);
            m_pMedallionServicePath[0] = '/';
            memcpy(m_pMedallionServicePath+1, p_InterfaceName, interfaceLen+1);
            char *ltmp = NULL;
            char *ctmp = m_pMedallionServicePath+1;
            while (*ctmp)
            {
                if(*ctmp == '.') {*ctmp = '/';ltmp = ctmp;}
                ctmp++;
            }
            if (ltmp) *ltmp = '\0';
            syslog(LOG_DEBUG, "DBUS_OBJ_PATH: %s", m_pMedallionServicePath);
        }
#endif
        if (m_pMedallionServicePath && m_pMedallionServiceMgrName) {
            syslog(LOG_DEBUG, "DBUS_OBJ_PATH: %s", m_pMedallionServicePath);
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
            if (pthread_create(&m_hThread, &attr, DbusCallWaitingThread, this) < 0) {
                syslog(LOG_DEBUG, "Thread Creation failed!!");
            }
            pthread_attr_destroy(&attr);
        }
    }

}

CDBusService::~CDBusService()
{
    void *status;
    if (m_pMedallionServicePath && m_pMedallionServiceMgrName) {
        pthread_join(m_hThread, &status);
    }

    if (m_pMedallionServiceMgrName) {
        delete[] m_pMedallionServiceMgrName;
    }

    if (m_pMedallionServicePath) {
        delete[] m_pMedallionServicePath;
    }
}

int CDBusService::IsValidDbusConnection()
{
    return !(!m_pConnection);
}

const char *CDBusService::GetInterFaceName()
{
    return m_pMedallionServiceMgrName;
}

const char *CDBusService::GetServiceObjectPathName()
{
    return m_pMedallionServicePath;
}

dbus_bool_t CDBusService::AddWatch(DBusWatch *t_pWatch, void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    return _dbus_loop_add_watch (pCd->loop, t_pWatch);
}

void CDBusService::RemoveWatch(DBusWatch *t_pWatch, void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    _dbus_loop_remove_watch (pCd->loop, t_pWatch);
}

void CDBusService::ToggleWatch(DBusWatch *t_pWatch, void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    _dbus_loop_toggle_watch (pCd->loop, t_pWatch);
}

dbus_bool_t CDBusService::AddTimeout(DBusTimeout *t_pTimeout, void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    return _dbus_loop_add_timeout (pCd->loop, t_pTimeout);
}

void CDBusService::RemoveTimeout (DBusTimeout *t_pTimeout, void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    _dbus_loop_remove_timeout (pCd->loop, t_pTimeout);
}

void CDBusService::DispatchStatusFunction (DBusConnection *t_pConnection, DBusDispatchStatus t_NewStatus, void *t_pData)
{
    DBusLoop *pLoop = reinterpret_cast<DBusLoop *>(t_pData);

    if (t_NewStatus != DBUS_DISPATCH_COMPLETE)
    {
        while (!_dbus_loop_queue_dispatch (pLoop, t_pConnection))
            _dbus_wait_for_memory ();
    }
}

void CDBusService::CDataFree(void *t_pData)
{
    CData *pCd = reinterpret_cast<CData *>(t_pData);

    dbus_connection_unref (pCd->connection);
    _dbus_loop_unref (pCd->loop);

    dbus_free (pCd);
}

CData* CDBusService::CDataNew(DBusLoop *t_pLoop, DBusConnection *t_pConnection)
{
    CData *pCd;

    pCd = dbus_new0 (CData, 1);
    if (pCd == NULL)
        return NULL;

    pCd->loop = t_pLoop;
    pCd->connection = t_pConnection;

    dbus_connection_ref (pCd->connection);
    _dbus_loop_ref (pCd->loop);

    return pCd;
}

void CDBusService::ServerDataFree (void *t_pData)
{
    ServerData *p_SD = reinterpret_cast<ServerData *>(t_pData);

    dbus_server_unref (p_SD->server);
    _dbus_loop_unref (p_SD->loop);

    dbus_free (p_SD);
}

ServerData* CDBusService::ServerDataNew(DBusLoop *t_pLoop, DBusServer *t_pServer)
{
    ServerData *p_SD;

    p_SD = dbus_new0 (ServerData, 1);

    if (p_SD == NULL)
        return NULL;

    p_SD->loop = t_pLoop;
    p_SD->server = t_pServer;

    dbus_server_ref (p_SD->server);
    _dbus_loop_ref (p_SD->loop);

    return p_SD;
}

dbus_bool_t CDBusService::AddServerWatch(DBusWatch *t_pWatch, void *t_pData)
{
    ServerData *pContext = reinterpret_cast<ServerData *>(t_pData);

    return _dbus_loop_add_watch (pContext->loop, t_pWatch);
}

void CDBusService::ToggleServerWatch(DBusWatch *t_pWatch, void *t_pData)
{
    ServerData *pContext = reinterpret_cast<ServerData *>(t_pData);

    _dbus_loop_toggle_watch (pContext->loop, t_pWatch);
}

void CDBusService::RemoveServerWatch(DBusWatch *t_pWatch, void *t_pData)
{
    ServerData *pContext = reinterpret_cast<ServerData *>(t_pData);

    _dbus_loop_remove_watch (pContext->loop, t_pWatch);
}

dbus_bool_t CDBusService::AddServerTimeout(DBusTimeout *t_pTimeout, void *t_pData)
{
    ServerData *pContext = reinterpret_cast<ServerData *>(t_pData);

    return _dbus_loop_add_timeout (pContext->loop, t_pTimeout);
}

void CDBusService::RemoveServerTimeout (DBusTimeout *t_pTimeout, void *t_pData)
{
    ServerData *pContext = reinterpret_cast<ServerData *>(t_pData);

    _dbus_loop_remove_timeout (pContext->loop, t_pTimeout);
}

dbus_bool_t CDBusService::TestConnectionSetup(DBusLoop *t_pLoop, DBusConnection *t_pConnection)
{
    CData *pCd;

    pCd = NULL;

    dbus_connection_set_dispatch_status_function (t_pConnection, DispatchStatusFunction, t_pLoop, NULL);

    pCd = CDataNew (t_pLoop, t_pConnection);

    if (pCd == NULL)
        goto NoMemory;

    if (!dbus_connection_set_watch_functions (t_pConnection, AddWatch, RemoveWatch, ToggleWatch, pCd, CDataFree))
        goto NoMemory;

    pCd = CDataNew (t_pLoop, t_pConnection);
    if (pCd == NULL)
        goto NoMemory;

    if (!dbus_connection_set_timeout_functions (t_pConnection, AddTimeout, RemoveTimeout, NULL, pCd, CDataFree))
        goto NoMemory;

    if (dbus_connection_get_dispatch_status (t_pConnection) != DBUS_DISPATCH_COMPLETE)
    {
        if (!_dbus_loop_queue_dispatch (t_pLoop, t_pConnection))
            goto NoMemory;
    }

    return TRUE;

NoMemory:

    if (pCd)
        CDataFree (pCd);

    dbus_connection_set_dispatch_status_function (t_pConnection, NULL, NULL, NULL);
    dbus_connection_set_watch_functions (t_pConnection, NULL, NULL, NULL, NULL, NULL);
    dbus_connection_set_timeout_functions (t_pConnection, NULL, NULL, NULL, NULL, NULL);

    return FALSE;
}

void CDBusService::TestConnectionShutdown(DBusLoop *t_pLoop, DBusConnection *t_pConnection)
{
    if (!dbus_connection_set_watch_functions (t_pConnection, NULL, NULL, NULL, NULL, NULL))
        _dbus_assert_not_reached ("setting watch functions to NULL failed");

    if (!dbus_connection_set_timeout_functions (t_pConnection, NULL, NULL, NULL, NULL, NULL))
        _dbus_assert_not_reached ("setting timeout functions to NULL failed");

    dbus_connection_set_dispatch_status_function (t_pConnection, NULL, NULL, NULL);
}

dbus_bool_t CDBusService::TestServerSetup(DBusLoop *t_pLoop, DBusServer *t_pServer)
{
    ServerData *pSD;

    pSD = ServerDataNew (t_pLoop, t_pServer);
    if (pSD == NULL)
        goto NoMemory;

    if (!dbus_server_set_watch_functions (t_pServer, AddServerWatch, RemoveServerWatch, ToggleServerWatch, pSD, ServerDataFree))
    {
        goto NoMemory;
    }

    pSD = ServerDataNew (t_pLoop, t_pServer);
    if (pSD == NULL)
        goto NoMemory;

    if (!dbus_server_set_timeout_functions (t_pServer, AddServerTimeout, RemoveServerTimeout, NULL, pSD, ServerDataFree))
    {
        goto NoMemory;
    }

    return TRUE;

NoMemory:
    if (pSD)
        ServerDataFree (pSD);

    TestServerShutdown (t_pLoop, t_pServer);

    return FALSE;
}

void CDBusService::TestServerShutdown(DBusLoop *t_pLoop, DBusServer *t_pServer)
{
    dbus_server_disconnect (t_pServer);

    if (!dbus_server_set_watch_functions (t_pServer, NULL, NULL, NULL, NULL, NULL))
        _dbus_assert_not_reached ("setting watch functions to NULL failed");

    if (!dbus_server_set_timeout_functions (t_pServer, NULL, NULL, NULL, NULL, NULL))
        _dbus_assert_not_reached ("setting timeout functions to NULL failed");
}

int CDBusService::DBusServiceManagerInitialize()
{
    /*DBus Service Routines*/
    DBusError       dbError;
    int             result;
    struct stat     sb;

    dbus_error_init (&dbError);

    syslog(LOG_DEBUG, "Starting dbus Initialization with stating dbus");
    /* Make sure dbus-daemon is up */
    while (stat("/dev/socket/dbus", &sb)) {
        syslog(LOG_DEBUG, "Failed to stat /dev/socket/dbus\n");
        usleep(500000);
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization with stating compeletion");
    m_pConnection = dbus_bus_get (DBUS_BUS_STARTER, &dbError);
    while (!m_pConnection)
    {
        dbus_error_free (&dbError);

        _dbus_sleep_milliseconds (100);

        m_pConnection = dbus_bus_get (DBUS_BUS_STARTER, &dbError);
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (connection got)");
    m_pLoop = _dbus_loop_new();
    if (m_pLoop == NULL)
    {
        syslog(LOG_DEBUG, "Error in _dbus_loop_new\n");
        dbus_connection_unref (m_pConnection);
        return -1;
    }
    syslog(LOG_DEBUG, "Starting dbus Initialization (new loop done)");

    if (!TestConnectionSetup (m_pLoop, m_pConnection))
    {
        syslog(LOG_DEBUG, "Error in test_connection_setup\n");
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (connection test done)");
    if (!dbus_connection_add_filter (m_pConnection, FilterFunction, this, NULL))
    {
        syslog(LOG_DEBUG, "Error in dbus_connection_add_filter\n");
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (add filter done)");
    if (!dbus_connection_register_object_path (m_pConnection, m_pMedallionServicePath, &m_pCallbackVtable, (void*)this))
    {
        syslog(LOG_DEBUG, "Error in dbus_connection_register_object_path\n");
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (object path set done)");
    void *pData;
    if (!dbus_connection_get_object_path_data (m_pConnection, m_pMedallionServicePath, &pData))
    {
        syslog(LOG_DEBUG, "Error in dbus_connection_get_object_path_data\n");
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (object path get done)");
    if (pData != (void*) this)
    {
        syslog(LOG_DEBUG, "dbus_connection_get_object_path_data() doesn't seem to work right\n");
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    syslog(LOG_DEBUG, "Starting dbus Initialization (object path valid data get done)");
    result = dbus_bus_request_name (m_pConnection, m_pMedallionServiceMgrName, 0, &dbError);
    if (dbus_error_is_set (&dbError))
    {
        syslog(LOG_DEBUG, "Failed to acquire service: %s\n", dbError.message);
        dbus_error_free (&dbError);
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }
    syslog(LOG_DEBUG, "Starting dbus Initialization (bus name allocation done)");

    if (result != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
    {
        syslog(LOG_DEBUG, "Failed to acquire service: %d\n", result);
        TestConnectionShutdown (m_pLoop, m_pConnection);
        dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);
        dbus_connection_unref (m_pConnection);
        _dbus_loop_unref (m_pLoop);
        return -1;
    }

    return 1;
}

int CDBusService::DBusServiceManagerRun(void)
{
    _dbus_loop_run (m_pLoop);

    TestConnectionShutdown (m_pLoop, m_pConnection);

    dbus_connection_remove_filter (m_pConnection, FilterFunction, NULL);

    dbus_connection_unref (m_pConnection);

    _dbus_loop_unref (m_pLoop);

    m_pLoop = NULL;

    dbus_shutdown ();

    return 1;
}

DBusHandlerResult CDBusService::FilterFunction(DBusConnection *t_pConnection, DBusMessage *t_pMessage, void *t_pUserData)
{
    CDBusService *cDbusSrvcObj = (CDBusService *)t_pUserData;
    if (dbus_message_is_signal (t_pMessage, cDbusSrvcObj->m_pMedallionServiceMgrName, "Disconnected"))
    {
        _dbus_loop_quit (cDbusSrvcObj->m_pLoop);

        return DBUS_HANDLER_RESULT_HANDLED;
    }
    else
    {
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }
}

#if 0
void CDBusService::PathUnregisteredFunction(DBusConnection  *t_pConnection, void *t_pUserData)
{
    /* connection was finalized */
}

#endif

/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Sending primitive to the specified interface.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pInterfaceName	: Interface name
 *		t_pMethodName		: name of the method
 *		t_iType				: Iterator
 *		t_pData				: Data to append to iterator
 *  @return
 *		void
 *
 ---------------------------------------------------------------------------*/
void CDBusService::SendPrimitiveToInterface(char *t_pInterfaceName, char *t_pMethodName, int t_iType, void *t_pData)
{
    DBusMessage *pMessage;
    DBusMessageIter itMessage;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_method_call (NULL, pObjPath, t_pInterfaceName, t_pMethodName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_message_iter_init_append (pMessage, &itMessage);

    if ( t_iType == DBUS_TYPE_STRING )
        dbus_message_iter_append_basic (&itMessage, t_iType, &t_pData);
    else
        dbus_message_iter_append_basic (&itMessage, t_iType, t_pData);

    dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);
}

/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Sending method to the specified interface.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pInterfaceName	: Interface name
 *		t_pMethodName		: name of the method
 *		t_pData				: Data
 *		t_nSize				: Size of data
 *  @return
 *		void
 *
 ---------------------------------------------------------------------------*/
void CDBusService::SendMethodToInterface(char *t_pInterfaceName, char *t_pMethodName, unsigned char *t_pData, int t_nSize)
{
    DBusMessage *pMessage;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_method_call (NULL, pObjPath, t_pInterfaceName, t_pMethodName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_message_append_args (pMessage, DBUS_TYPE_ARRAY, DBUS_TYPE_BYTE, &t_pData, t_nSize, DBUS_TYPE_INVALID);

    dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);
}

void CDBusService::SendMethodToInterface(char *t_pInterfaceName, char *t_pMethodName, int iArgType1, void *pArg1, int iArgType2, void *pArg2)
{
    DBusMessage *pMessage;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_method_call (NULL, pObjPath, t_pInterfaceName, t_pMethodName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_message_append_args(pMessage, iArgType1, pArg1, iArgType2, pArg2, DBUS_TYPE_INVALID);

    dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);
}

/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Sending method to the specified interface without data.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pInterfaceName	: Interface name
 *		t_pMethodName		: name of the method
 *  @return
 *		dbus_bool_t		: TRUE on success
 *
 ---------------------------------------------------------------------------*/
dbus_bool_t CDBusService::SendMethodToInterfaceNoArgs(char *t_pInterfaceName, char *t_pMethodName)
{
    DBusMessage *pMessage;
    dbus_bool_t ret = FALSE;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_method_call (NULL, pObjPath, t_pInterfaceName, t_pMethodName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    ret = dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);

    return ret;
}

/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Sending method to the specified interface with data.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pInterfaceName	: Interface name
 *		t_pMethodName		: name of the method
 *		t_pData			: data
 *		t_nSize			: size of data
 *  @return
 *		dbus_bool_t		: TRUE on success
 *
 ---------------------------------------------------------------------------*/
dbus_bool_t CDBusService::SendMethodToInterfaceArgs(char *t_pInterfaceName, char *t_pMethodName, const char *t_pData, int t_nSize)
{
    DBusMessage *pMessage;
    dbus_bool_t ret = FALSE;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_method_call (NULL, pObjPath, t_pInterfaceName, t_pMethodName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_message_append_args (pMessage, DBUS_TYPE_ARRAY, DBUS_TYPE_BYTE, &t_pData, t_nSize, DBUS_TYPE_INVALID);

    ret = dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);

    return ret;
}

/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Sending signal from the interface.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pInterfaceName	: Interface name
 *		t_pSignalName		: Signal name
 *  @return
 *		void
 *
 ---------------------------------------------------------------------------*/
void CDBusService::SendSignalToInterface(char *t_pInterfaceName, char *t_pSignalName)
{
    DBusMessage *pMessage;
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);

    pMessage = dbus_message_new_signal (pObjPath, t_pInterfaceName, t_pSignalName);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);
}

void CDBusService::RelayMessageToInterface(char *t_pInterfaceName, DBusMessage * pMsg)
{
    char *pObjPath = GetObjectPathByInterface(t_pInterfaceName);
    DBusMessage *pMessage = dbus_message_copy(pMsg);

    dbus_message_set_path (pMessage, pObjPath);

    FreeObjectPathRetrievedByInterface(pObjPath);

    dbus_message_set_interface (pMessage, t_pInterfaceName);

    dbus_message_set_destination (pMessage, t_pInterfaceName);

    dbus_connection_send (m_pConnection, pMessage, NULL);

    dbus_connection_flush (m_pConnection);

    dbus_message_unref (pMessage);
}

#if 1
/**---------------------------------------------------------------------------
 * Routine description:
 *  @brief
 *			Message function to handle messages.
 *---------------------------------------------------------------------------
 * Parameters description:
 *  @param
 *		t_pConnection	: D-bus connection
 *		t_pMessage		: received message
 *		t_pUserData		: arguments with the message
 *  @return
 *		returns one of the following
 *			DBUS_HANDLER_RESULT_HANDLED 		: Message has had its effect - no need to run more handlers.
 *			DBUS_HANDLER_RESULT_NOT_YET_HANDLED : Message has not had any effect - see if other handlers want it.
 * 			DBUS_HANDLER_RESULT_NEED_MEMORY 	: Need more memory
 *
 ---------------------------------------------------------------------------*/
DBusHandlerResult CDBusService::DefaultPathMessageFunction(DBusConnection *t_pConnection, DBusMessage *t_pMessage, void *t_pUserData)
{
    return DBUS_HANDLER_RESULT_HANDLED;
}
#endif
