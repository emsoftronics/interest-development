/*
 * =====================================================================================
 *
 *       Filename:  llist.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 26 June 2017 08:07:30  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */

#ifndef __LLIST_H__
#define __LLIST_H__

extern void *llist_getObject(unsigned int id, unsigned int size);
extern void *llist_createObject(unsigned int id, unsigned int size);
extern int llist_deleteObject(unsigned int id, unsigned int size);
extern unsigned int llist_getObjectCount(void);

#endif /* __LLIST_H__ */
