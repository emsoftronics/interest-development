/*
 * =====================================================================================
 *
 *       Filename:  sipc.h
 *
 *    Description:  SIPC exported functions
 *
 *        Version:  1.0
 *        Created:  Monday 26 June 2017 12:31:46  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  LNT Technology & Services
 *
 * =====================================================================================
 */

#ifndef __SIPC_H__
#define __SIPC_H__

#define DEFAULT_SOCKET_PATH     "\0hidden"
/*------------- SIPC Server functions ------------------*/
extern int sipc_startServer(char *socket_path);

/*-------------- Client Functions ----------------------*/
extern int sipc_connectToServer(char *socket_path);
extern void sipc_disconnectFromServer(int sd);
extern int sipc_allocDataBlock(int sd, unsigned int id, void *storage, unsigned int size);
extern int sipc_freeDataBlock(int sd, unsigned int id, unsigned int size);
extern int sipc_getData(int sd, unsigned int id, void *storage, unsigned int size);
extern int sipc_setData(int sd, unsigned int id, void *data, unsigned int size);
#endif /*  __SIPC_H__ */
