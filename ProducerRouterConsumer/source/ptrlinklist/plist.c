/*
 * =====================================================================================
 *
 *       Filename:  plist.c
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


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "plist.h"
#define SIGNED_MAX_VAL(x) ((typeof(x))(((typeof(x))(~(0))) >> 1))
//#define SIGNED_MAX_VAL(x) ((typeof(x))(1) << ((sizeof(x)<<3)-1))
struct pl_list;

struct pl_node {
    struct pl_node *next;
    void *dataptr;
    unsigned long datalen;
};

struct pl_list {
    struct pl_node *first_entry;
    struct pl_node *last_entry;
    unsigned int item_count;
    int   sorted_flag;
    pcompare_t item_compare;
    pthread_mutex_t lock;
};

plist_ref_t pl_createList(plist_sort_type_t sort_type, pcompare_t compare_handler)
{
    int ret = 0;
    struct pl_list *list = malloc(sizeof(struct pl_list));
    if (!list) {
        errno = ENOMEM;
        return NULL;
    }
    list->first_entry = list->last_entry = NULL;
    list->item_count = 0;
    list->sorted_flag = (compare_handler)? sort_type : PL_SORT_NONE;
    list->item_compare = compare_handler;
    if ((ret = pthread_mutex_init(&list->lock, NULL)) != 0 ) {
        free(list);
        errno = (ret < 0)? -ret : ret;
        return NULL;
    }
    return list;
}

void pl_destroyList(plist_ref_t *plist)
{
    if ((!plist) || (! *plist)) return;
    struct pl_list *list = *((struct pl_list **)plist);
    pl_clear(list);
    pthread_mutex_destroy(&list->lock);
    free(list);
    *plist = NULL;
}

int pl_getListItemCount(plist_ref_t plist)
{
    struct pl_list *list = (struct pl_list *)plist;
    int count = 0;
    pthread_mutex_lock(&list->lock);
    count = list->item_count;
    pthread_mutex_unlock(&list->lock);
    return count;
}

int pl_clear(plist_ref_t plist)
{
    struct pl_list *list = (struct pl_list *)plist;
    struct pl_node *tmp = NULL;
    struct pl_node *ddd = NULL;

    if (!list) return -EINVAL;
    pthread_mutex_lock(&list->lock);
    tmp = list->first_entry;
    while (tmp != NULL) {
        ddd = tmp;
        tmp = tmp->next;
        if (ddd->dataptr) free(ddd->dataptr);
        free(ddd);
    }
    list->item_count = 0;
    list->first_entry = list->last_entry = NULL;
    pthread_mutex_unlock(&list->lock);

    return 0;
}


int pl_addAtTail(plist_ref_t plist, void *data, unsigned int data_length)
{
    struct pl_list *list = (struct pl_list *)plist;
    struct pl_node *tmp = NULL;
    if ((!data) || (!list)) return -EINVAL;
    tmp = (struct pl_node *)malloc(sizeof(struct pl_node));
    if (!tmp) return -ENOMEM;
    tmp->datalen = data_length;
    tmp->dataptr = data;
    tmp->next = NULL;
    pthread_mutex_lock(&list->lock);
    if (list->first_entry == NULL) list->first_entry = tmp;

    if (list->last_entry == NULL) list->last_entry = tmp;
    else {
        list->last_entry->next = tmp;
        list->last_entry = tmp;
    }
    list->item_count++;
    list->sorted_flag = PL_SORT_NONE;
    pthread_mutex_unlock(&list->lock);
    return 0;
}

int pl_addAtHead(plist_ref_t plist, void *data, unsigned int data_length)
{
    struct pl_list *list = (struct pl_list *)plist;
    int ret = -1;
    struct pl_list temp = {.first_entry = NULL,
                            .last_entry = NULL,
                            .lock = PTHREAD_MUTEX_INITIALIZER,
                            .item_count = 0,
                          };
    if ((!list) || (!data)) return -EINVAL;
    ret = pl_addAtTail(&temp, data, data_length);
    if (ret < 0) return ret;

    pthread_mutex_lock(&list->lock);
    temp.first_entry->next = list->first_entry;
    list->first_entry = temp.first_entry;
    if (!list->last_entry) list->last_entry = list->first_entry;
    list->item_count++;
    list->sorted_flag = PL_SORT_NONE;
    pthread_mutex_unlock(&list->lock);
    return 0;
}


static int pl_addToListSortedByData(plist_ref_t plist, void *data, unsigned int data_length)
{
    struct pl_list *list = (struct pl_list *)plist;
    struct pl_node *tmp = NULL;
    struct pl_node *p = NULL;
    struct pl_node *c = NULL;
    if ((!data) || (!list)) return -EINVAL;
    if (!list->item_compare || (list->sorted_flag == PL_SORT_NONE))
        return pl_addAtTail(list, data, data_length);
    tmp = (struct pl_node *)malloc(sizeof(struct pl_node));
    if (!tmp) return -ENOMEM;
    tmp->dataptr = data;
    tmp->datalen = data_length;
    tmp->next = NULL;

    pthread_mutex_lock(&list->lock);
    for (c = list->first_entry; c != NULL; c = c->next) {
        if ((list->sorted_flag == PL_SORT_ASC)
                && (list->item_compare(data, c->dataptr) < 0)) break;
        if ((list->sorted_flag == PL_SORT_DSC)
                && (list->item_compare(data, c->dataptr) > 0)) break;
        p = c;
    }
    if (!c && !p) {
        list->first_entry = list->last_entry = tmp;
    }
    else if (!c && p) {
        list->last_entry->next = tmp;
        list->last_entry = tmp;
    }
    else if (!p && c) {
        tmp->next = list->first_entry;
        list->first_entry = tmp;
    }
    else {
        tmp->next = c;
        p->next = tmp;
    }
    list->item_count++;
    pthread_mutex_unlock(&list->lock);
    return 0;
}

int pl_addToList(plist_ref_t plist, void *data, unsigned int data_length)
{
    return pl_addToListSortedByData(plist, data, data_length);
}

int pl_removeFromHead(plist_ref_t plist, void **outbuf)
{
    struct pl_list *list = (struct pl_list *)plist;
    int length = 0;
    void *tmp = NULL;
    if (!list) return -EINVAL;
    if (!list->first_entry) return -ENOENT;
    pthread_mutex_lock(&list->lock);
    if (outbuf) {
        *outbuf = list->first_entry->dataptr;
        length = list->first_entry->datalen;
    }
    tmp = list->first_entry;
    list->first_entry = list->first_entry->next;
    if (!list->first_entry) list->last_entry = NULL;
    list->item_count--;
    pthread_mutex_unlock(&list->lock);
    free(tmp);
    return length;
}


int pl_removeFromTail(plist_ref_t plist, void **outbuf)
{
    struct pl_list *list = (struct pl_list *)plist;
    int length = 0;
    struct pl_node *tmp = NULL;
    if (!list) return -EINVAL;
    if (!list->first_entry) return -ENOENT;
    pthread_mutex_lock(&list->lock);
    for(list->last_entry = list->first_entry;
                (list->last_entry->next != NULL) && (list->last_entry->next->next != NULL);
                list->last_entry = list->last_entry->next);

    if (!list->last_entry->next) {
        tmp = list->last_entry;
        list->last_entry = list->first_entry = NULL;
    }
    else {
        tmp = list->last_entry->next;
        list->last_entry->next = NULL;
    }
    if (outbuf) {
        *outbuf = tmp->dataptr;
        length = tmp->datalen;
    }
    list->item_count--;
    pthread_mutex_unlock(&list->lock);
    free(tmp);
    return length;
}

int pl_removeByRef(plist_ref_t plist, void *ref)
{
    struct pl_list *list = (struct pl_list *)plist;
    int length = -ENAVAIL;
    struct pl_node *p = NULL;
    struct pl_node *c = NULL;
    if (!list) return -EINVAL;
    if (!list->first_entry) return -ENOENT;
    pthread_mutex_lock(&list->lock);
    for(c = list->first_entry; c != NULL; c = c->next) {
        if (c->dataptr == ref) break;
        p = c;
    }

    if (c) {
        if (!p) list->first_entry = c->next;
        else p->next = c->next;

        if (!c->next) list->last_entry = p;
        length = c->datalen;
        list->item_count--;
        free(c);
    }
    pthread_mutex_unlock(&list->lock);
    return length;
}


int pl_getByRef(plist_ref_t plist, void *ref)
{
    struct pl_list *list = (struct pl_list *)plist;
    struct pl_node *t;
    int len = -1;

    if (!list) {
        errno = EINVAL;
        return -EINVAL;
    }
    pthread_mutex_lock(&list->lock);
    for(t = list->first_entry; t != NULL; t = t->next) {
        if (t->dataptr == ref) break;
    }

    if(!t) errno = ENAVAIL;
    else len = t->datalen;
    pthread_mutex_unlock(&list->lock);

    return len;
}

void *pl_getDataUsingCompMethod(plist_ref_t plist, psearch_t cmethod, long keydata)
{
    struct pl_list *list = (struct pl_list *)plist;
    struct pl_node *t;
    void *ret = NULL;

    if (!list) {
        errno = EINVAL;
        return NULL;
    }
    pthread_mutex_lock(&list->lock);
    for(t = list->first_entry; t != NULL; t = t->next) {
        if (cmethod(t->dataptr, keydata) > 0) break;
    }

    if(!t) errno = ENAVAIL;
    else ret = t->dataptr;
    pthread_mutex_unlock(&list->lock);

    return ret;
}

#if 0
static void pl_swap(plist_ref_t plist, struct pl_node *prev)
{
    struct pl_list *list = plist;
    struct pl_node *cur = NULL;
    if (!list || !list->first_entry) return;
    if ((!prev) && list->first_entry->next) {
        cur = list->first_entry;
        list->first_entry = cur->next;
        cur->next = cur->next->next;
        list->first_entry->next = cur;
    }
    else if (prev && prev->next && prev->next->next){
        cur = prev->next;
        prev->next = cur->next;
        cur->next = prev->next->next;
        prev->next->next = cur;
    }

    if (cur && !cur->next) list->last_entry = cur;
}

int pl_sortList(plist_ref_t plist, plist_sort_type_t sort_type)
{
    struct pl_list *list = plist;
    struct pl_node *cur = NULL;
    struct pl_node *prev = NULL;
    int swap = 0, count, comp, i;
    void *cur_data, *next_data;
    if (!list) return -EINVAL;
    if (sort_type == SORTED_NONE) {
        list->sorted_flag = sort_type;
        return 0;
    }
    if (!list->first_entry) return -ENOENT;
    pthread_mutex_lock(&list->lock);

    for(count = 0; count < list->item_count; count++)
    for(cur = list->first_entry, prev = NULL, i = 0;
            (i < list->item_count - count) && (cur->next != NULL);
            cur = cur->next, i++) {
        swap = 0;
        cur_data = (char *)cur + sizeof(struct pl_node);
        next_data = (char *)(cur->next) + sizeof(struct pl_node);
        if (list->item_compare  && ((sort_type == SORTED_BY_DCF) || (sort_type == SORTED_REV_BY_DCF))) {
            comp = list->item_compare(cur_data, next_data);
            if (((comp > 0) && (sort_type == SORTED_BY_DCF))
                    || ((comp < 0) && (sort_type == SORTED_REV_BY_DCF))) swap = 1;
        }
        else {
            if (((cur->item_id > cur->next->item_id) && (sort_type == SORTED_BY_ID))
                    || ((cur->item_id < cur->next->item_id) && (sort_type == SORTED_REV_BY_ID))) swap = 1;
        }

        if (swap) {
            pl_swap(list, prev);
            if (!prev) cur = list->first_entry;
            else cur = prev->next;
        }
        prev = cur;
    }
    list->sorted_flag = sort_type;
    pthread_mutex_unlock(&list->lock);
    return 0;
}

void *pl_getListItem(plist_traverse_t cmd, plist_ref_t plist, int *item_size, int *data_type)
{
    struct pl_list *list = plist;
    static struct pl_node *tmp = NULL;
    static struct pl_node *head = NULL;
    static int count = 0;
    struct pl_node *t = NULL;
    void *mem = NULL;
    int ret = 0;


    if (!list) {errno = EINVAL; return NULL;}
    if (!list->first_entry) {errno = ENOENT; return NULL;}

    pthread_mutex_lock(&list->lock);
    if ((head != list->first_entry) || (count != list->item_count)) {
        tmp = head = list->first_entry;
        count = list->item_count;
    }

    switch(cmd) {
        case ITEM_BEGIN:
            t = tmp = list->first_entry;
            break;
        case ITEM_NEXT:
            if (tmp) tmp = tmp->next;
            t = tmp;
            break;
        case ITEM_END:
            t = tmp = list->last_entry;
            break;
        case ITEM_FIRST:
            t = list->first_entry;
            break;
        case ITEM_LAST:
            t = list->last_entry;
            break;
        default: ret = -EINVAL;
    }

    if(ret < 0) errno = - ret;
    else if (!t) errno =  ENOENT;
    else {
        mem = ((char *)t) + sizeof(struct pl_node);
        if (item_size) *item_size = t->item_length;

        if (data_type) *data_type = t->item_type;
    }
    pthread_mutex_unlock(&list->lock);
    return mem;
}

#endif

