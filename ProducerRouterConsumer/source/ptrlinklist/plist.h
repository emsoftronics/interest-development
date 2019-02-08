/*
 * =====================================================================================
 *
 *       Filename:  plist.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 01 February 2019 12:50:10  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), jagdish.prajapati@ltts.com
 *        Company:  L&T Technology & Services
 *
 * =====================================================================================
 */


#ifndef __PLIST_H__
#define __PLIST_H__

typedef enum {
    PL_ITEM_BEGIN  = 0,
    PL_ITEM_NEXT   = 1,
    PL_ITEM_END    = 2,
    PL_ITEM_FIRST  = 3,
    PL_ITEM_LAST   = 4
} plist_traverse_t;

typedef enum {
    PL_SORT_DSC        = -1,
    PL_SORT_NONE       = 0,
    PL_SORT_ASC        = 1,
} plist_sort_type_t;


typedef void *plist_ref_t;

typedef int (*pcompare_t)(void *, void*); /* return 0 => equal, -1 => less, 1 => greater */
typedef int (*psearch_t) (void *, long);

extern plist_ref_t pl_createList(plist_sort_type_t sort_type, pcompare_t compare_handler);
extern void pl_destroyList(plist_ref_t *list);

extern int pl_getListItemCount(plist_ref_t list);
extern int pl_clear(plist_ref_t list);

extern int pl_addToList(plist_ref_t list, void *data, unsigned int data_length);

extern int pl_addAtHead(plist_ref_t list, void *data, unsigned int data_length);
extern int pl_addAtTail(plist_ref_t list, void *data, unsigned int data_length);

extern int pl_removeFromHead(plist_ref_t list, void **outbuf);
extern int pl_removeFromTail(plist_ref_t list, void **outbuf);
extern int pl_removeByRef(plist_ref_t list, void *ref);
extern int pl_getByRef(plist_ref_t list, void *ref);
extern void *pl_getDataUsingCompMethod(plist_ref_t list, psearch_t cmethod, long keydata);
//extern int pl_sortList(plist_ref_t list, plist_sort_type_t sort_type);
//extern void *pl_getListItem(plist_traverse_t cmd, plist_ref_t list, int *item_size, int *data_type);


#endif /* __LINKLIST_H__ */
