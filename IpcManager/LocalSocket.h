/*
 * =====================================================================================
 *
 *       Filename:  LocalSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wednesday 19 July 2017 09:41:21  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */


#ifndef __LOCALSOCKET_H__
#define __LOCALSOCKET_H__

#define SOCKET_MAX_CLIENTS  10


typedef void (*recieveCallback_t) (int, int, char*, int);

virtual class LocalSocket {
    protected:
        int mSocket;
        char *mSocketName;
        recieveCallback_t mRecieveCallback;
    public:
        LocalSocket(const char *socketName, recieveCallback_t recieveCallback);
        ~LocalSocket(void);

        char *GetSocketName(void);
        int SendData(int srcId, int dstID, char *data, int dataLen);
};

class LocalServerSocket : public LocalSocket {
    public:
        int HandleClients(void);
}

class LocalClientSocket : public LocalSocket {
    public:
        int ConnectToServer(void);
}

#endif /* __LOCALSOCKET_H__ */

