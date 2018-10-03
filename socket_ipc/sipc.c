/*
 * =====================================================================================
 *
 *       Filename:  sipc.c
 *
 *    Description:  This file includes some wrapper function to start socket ipc service
 *                  and client connection with some functions for getting and setting
 *                  shared data between the clients.
 *
 *        Version:  1.0
 *        Created:  Saturday 24 June 2017 12:32:10  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  LNT Technology & Services
 *
 * =====================================================================================
 */

/**
    Handle multiple socket connections with select and fd_set on Linux

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> /* FD_SET, FD_ISSET, FD_ZERO macros */
#include <sys/un.h>
#include "llist.h"

#define TRUE   1
#define FALSE  0

#define MAX_CLIENTS             3
#define MAX_BUFFER_SIZE         255

enum sipc_data {
    SIPC_IO_ERROR = 0,
    SIPC_INVALID_ID,
    SIPC_STATUS_CONNECTED,
    SIPC_STATUS_EXISTS,
    SIPC_STATUS_ALLOCATED,
    SIPC_STATUS_FREED,
    SIPC_STATUS_GOT,
    SIPC_STATUS_WROTE,
    SIPC_ACTION_ALLOCATE,
    SIPC_ACTION_FREE,
    SIPC_ACTION_GET,
    SIPC_ACTION_PUT,
};

typedef struct {
    unsigned int sipc_id;
    int sipc_data_type;
    unsigned int length;
} sipc_header_t;

typedef struct {
    sipc_header_t header;
    unsigned char data[MAX_BUFFER_SIZE];
} sipc_packet_t;

static int server_context = FALSE; /* To monitor SIPC service context */
static sipc_packet_t buffer;  /* IPC data buffer */

#if 0
static char object[MAX_BUFFER_SIZE];
static void *getObject(unsigned int id, unsigned int size) {
    if (id == 1) return object;
    else return NULL;
}

static void *createObject(unsigned int id, unsigned int size) {
    if (id == 1) return object;
    else return NULL;
}

static int deleteObject(unsigned int id, unsigned int size) {
    if (id == 1) return 0;
    else return -1;
}
#endif

static void sipc_sendResponse(int sd, int size)
{
    char *obj = NULL;
    int length = sizeof(sipc_header_t);

    if (size >= sizeof(sipc_header_t)) {
        switch(buffer.header.sipc_data_type)
        {
        case SIPC_ACTION_ALLOCATE:
            obj = llist_getObject(buffer.header.sipc_id, buffer.header.length);
            if (obj == NULL) {
                obj = llist_createObject(buffer.header.sipc_id, buffer.header.length);
                if (obj == NULL) {
                    buffer.header.sipc_data_type = SIPC_INVALID_ID;
                }
                else {
                    buffer.header.sipc_data_type = SIPC_STATUS_ALLOCATED;
                    memcpy(buffer.data, obj, buffer.header.length);
                    length += buffer.header.length;
                }
            }
            else {
                buffer.header.sipc_data_type = SIPC_STATUS_EXISTS;
                memcpy(buffer.data, obj, buffer.header.length);
                length += buffer.header.length;
            }
        break;
        case SIPC_ACTION_FREE:
            if (llist_deleteObject(buffer.header.sipc_id, buffer.header.length) < 0) {
                buffer.header.sipc_data_type = SIPC_INVALID_ID;
            }
            else {
                buffer.header.sipc_data_type = SIPC_STATUS_FREED;
            }
        break;
        case SIPC_ACTION_GET:
            obj = llist_getObject(buffer.header.sipc_id, buffer.header.length);
            if (obj == NULL) {
                buffer.header.sipc_data_type = SIPC_INVALID_ID;
            }
            else {
                buffer.header.sipc_data_type = SIPC_STATUS_GOT;
                memcpy(buffer.data, obj, buffer.header.length);
                length += buffer.header.length;
            }
        break;
        case SIPC_ACTION_PUT:
            obj = llist_getObject(buffer.header.sipc_id, buffer.header.length);
            if (obj == NULL) {
                buffer.header.sipc_data_type = SIPC_INVALID_ID;
            }
            else {
                memcpy(obj, buffer.data, buffer.header.length);
                buffer.header.sipc_data_type = SIPC_STATUS_WROTE;
                length += buffer.header.length;
            }
        break;
        default:
            buffer.header.sipc_data_type = SIPC_IO_ERROR;
        break;
       }
    }
    else {
        buffer.header.sipc_data_type = SIPC_IO_ERROR;
        printf("Socket Read Error!!\n");
    }
    if (write(sd, &buffer, length) != length) {
        perror("socket write");
    }
}

int sipc_startServer(char *socket_path)
{
    int opt = TRUE;
    int master_socket;
    int addrlen;
    int new_socket;
    int client_socket[MAX_CLIENTS] = {0};
    int activity, i , valread , sd;
    int max_sd;
    struct sockaddr_un address;

    server_context = TRUE;

    /* set of socket descriptors */
    fd_set readfds;

    /* create a master socket */
    if( (master_socket = socket(AF_UNIX , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        return -1;
    }

    /* set master socket to allow multiple connections , this is just a good habit, it will work without this */
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        return -1;
    }

    /* type of socket created */
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socket_path, sizeof(address.sun_path)-1);

    /* bind the socket to unix address */
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return -1;
    }

    /* try to specify maximum of 3 pending connections for the master socket */
    if (listen(master_socket, MAX_CLIENTS) < 0)
    {
        perror("listen failed");
        return -1;
    }

    /* accept the incoming connection */
    addrlen = sizeof(address);
    printf("Waiting for connections ...\n");

    while(TRUE)
    {
        /* clear the socket set */
        FD_ZERO(&readfds);

        /* add master socket to set */
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        /* add child sockets to set */
        for ( i = 0 ; i < MAX_CLIENTS ; i++)
        {
            /* socket descriptor */
            sd = client_socket[i];

            /* if valid socket descriptor then add to read list */
            if(sd > 0)
                FD_SET( sd , &readfds);

            /* highest file descriptor number, need it for the select function */
            if(sd > max_sd)
                max_sd = sd;
        }

        /* wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely */
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error!!\n");
        }

        /* If something happened on the master socket , then its an incoming connection */
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                return -1;
            }

            /* inform user of socket number - used in send and receive commands */
            printf("new connection: %d\n", new_socket);
#if 0
            /* send new connection starting message */
            char *buf = (char *) (&buffer);
            strcpy(buf, "Welcome Buddy!! you are connected to server.\n");
            //buffer.sipc_data_type = (unsigned char)SIPC_STATUS_CONNECTED;
            if( write(new_socket, buf, strlen(buf)+1) != strlen(buf)+1)
            {
                perror("send");
            }
#endif
            /* add new socket to array of sockets */
            for (i = 0; i < MAX_CLIENTS; i++)
            {
                /* if position is empty */
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
        }

        /* else its some IO operation on some other socket */
        for (i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
                /* Check if it was for closing , and also read the incoming message */
                if ((valread = read( sd , &buffer, sizeof(buffer))) == 0)
                {
                    /*Somebody disconnected , get his details and print*/
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("disconnected : %d\n", sd);

                    /* Close the socket and mark as 0 in list for reuse */
                    close( sd );
                    client_socket[i] = 0;
                }
                else
                {
                    /* Reply the recieved message */
                    sipc_sendResponse(sd, valread);
                }
            }
        }
    }
    return 0;
}


int sipc_connectToServer(char *socket_path)
{
    int cSocket;
    struct sockaddr_un addr;

    if (server_context == TRUE) {
        return 0x0ffff;
    }

    /* Create client socket */
    if((cSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n");
        return -1;
    }

    /* Assigning socket type and address */
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    /* Try to connect to socket ipc server */
    if(connect(cSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0 ) {
        perror("connection error");
        close(cSocket);
        return -1;
    }

    return cSocket;
}

void sipc_disconnectFromServer(int sd)
{
    if (server_context != TRUE) {
        close(sd);
    }
}

int sipc_allocDataBlock(int sd, unsigned int id, void *storage, unsigned int size)
{
    int ret = -1;

    if (server_context == TRUE) {
        char *tbuf = llist_createObject(id, size);
        if ( tbuf != NULL) {
            memcpy(storage, tbuf, size);
            return size;
        }
        else return -1;
    }

    buffer.header.sipc_id = id;
    buffer.header.sipc_data_type = SIPC_ACTION_ALLOCATE;
    buffer.header.length = size;
    if (write(sd, &buffer, sizeof(sipc_header_t)) != sizeof(sipc_header_t)) {
        perror("write");
        return -1;
    }

    ret = read(sd, &buffer, sizeof(sipc_packet_t));
    if ((ret == sizeof(sipc_header_t) + size) && ((buffer.header.sipc_data_type
                == SIPC_STATUS_ALLOCATED) || (buffer.header.sipc_data_type
                == SIPC_STATUS_EXISTS))) {
        memcpy(storage, buffer.data, size);
    }
    else {
        printf("%s : ret = %d, buffer.header.sipc_data_type = %d\n", __func__,
                ret, buffer.header.sipc_data_type);
        return -1;
    }

    return size;
}

int sipc_freeDataBlock(int sd, unsigned int id, unsigned int size)
{
    int ret = -1;

    if (server_context == TRUE) {
        return llist_deleteObject(id, size);
    }

    buffer.header.sipc_id = id;
    buffer.header.sipc_data_type = SIPC_ACTION_FREE;
    buffer.header.length = size;
    if (write(sd, &buffer, sizeof(sipc_header_t)) != sizeof(sipc_header_t)) {
        perror("write");
        return -1;
    }

    ret = read(sd, &buffer, sizeof(sipc_packet_t));
    if ((ret == sizeof(sipc_header_t)) && (buffer.header.sipc_data_type
                == SIPC_STATUS_FREED)) {
        return 0;
    }
    else {
        return -1;
    }
}

int sipc_getData(int sd, unsigned int id, void *storage, unsigned int size)
{
    int ret = -1;

    if (server_context == TRUE) {
        char *tbuf = llist_getObject(id, size);
        if ( tbuf != NULL) {
            memcpy(storage, tbuf, size);
            return size;
        }
        else return -1;
    }

    buffer.header.sipc_id = id;
    buffer.header.sipc_data_type = SIPC_ACTION_GET;
    buffer.header.length = size;
    if (write(sd, &buffer, sizeof(sipc_header_t)) != sizeof(sipc_header_t)) {
        perror("write");
        return -1;
    }

    ret = read(sd, &buffer, sizeof(sipc_packet_t));
    if ((ret == sizeof(sipc_header_t) + size) && (buffer.header.sipc_data_type
                == SIPC_STATUS_GOT)) {
        memcpy(storage, buffer.data, size);
    }
    else {
        return -1;
    }

    return size;
}

int sipc_setData(int sd, unsigned int id, void *data, unsigned int size)
{
    int ret = -1;

    if (server_context == TRUE) {
        char *tbuf = llist_getObject(id, size);
        if (tbuf != NULL) {
            memcpy(tbuf, data, size);
            return size;
        }
        else return -1;
    }

    buffer.header.sipc_id = id;
    buffer.header.sipc_data_type = SIPC_ACTION_PUT;
    buffer.header.length = size;
    memcpy(buffer.data, data, size);
    if (write(sd, &buffer, sizeof(sipc_header_t) + size)
            != sizeof(sipc_header_t) + size) {
        perror("write");
        return -1;
    }

    ret = read(sd, &buffer, sizeof(sipc_packet_t));
    if ((ret == sizeof(sipc_header_t) + size) && (buffer.header.sipc_data_type
                == SIPC_STATUS_WROTE)) {
        return size;
    }
    else {
        perror("read");
        return -1;
    }
}

