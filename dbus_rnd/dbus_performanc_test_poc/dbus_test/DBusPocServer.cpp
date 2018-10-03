#include <syslog.h>
#include "DBusService.h"
#include <unistd.h>

static void delay(int count)
{
    int i,j;
    for (i = 0; i < count; i++) {
        for(j = 0; j < 1000; j++);
    }
}

static DBusHandlerResult PathMessageFunction(DBusConnection *t_pConnection, DBusMessage *t_pMessage, void *t_pUserData)
{
    DBusHandlerResult dbResult = DBUS_HANDLER_RESULT_HANDLED;
    DBusError dbError;
    CDBusService *dbusServiceObj = (CDBusService *)t_pUserData;
    unsigned char *pByteArray;
    int len;
    char lMethod[] = "f0";
    char lSignal[] = "s0";
    int fns;

    dbus_error_init(&dbError);

    for ( fns = 0; fns < 4; fns++) {
        lMethod[1] ++;
        lSignal[1] ++;
        syslog(LOG_DEBUG, "Checking for Method : %s.%s", dbusServiceObj->GetInterFaceName(), lMethod);
        if(dbus_message_is_method_call (t_pMessage, dbusServiceObj->GetInterFaceName(), lMethod))
        {
            syslog(LOG_DEBUG, "Called Method : %s.%s", dbusServiceObj->GetInterFaceName(), lMethod);
            if(dbus_message_get_args(t_pMessage, &dbError, DBUS_TYPE_ARRAY, DBUS_TYPE_BYTE, &pByteArray,
                        &len, DBUS_TYPE_INVALID)) {
                //usleep(100000);
//                delay(100);
                syslog(LOG_DEBUG, "Called by Interface : %s", pByteArray);
                dbusServiceObj->SendSignalToInterface((char *)pByteArray, lSignal);
            }
            break;
        }
    }

    return dbResult;
}

int main(int argc, char **argv)
{
    int counter = 0;
    int interface_count = argc - 1;
    char **interfaces = argv;

    CDBusService *cbsObj[20];
    for (counter = 0; counter < interface_count; counter++) {
        cbsObj[counter] = new CDBusService(interfaces[counter+1], PathMessageFunction);
    }
    while (1) {
        sleep(30);
    }
    for (counter = 0; counter < interface_count; counter++) {
        delete cbsObj[counter];
    }
}

