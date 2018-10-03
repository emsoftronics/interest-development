/*
 * =====================================================================================
 *
 *       Filename:  llist.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Monday 26 June 2017 06:46:18  IST
 *       Revision:  1.1
 *       Compiler:  gcc
 *
 *         Author:  Jagdish Prajapati (JP), prajapatijagdish@gmail.com
 *        Company:  Emsoftronic
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>

struct llist_data_object;

typedef struct llist_data_object {
    unsigned int id;
    unsigned int data_length;
    void *data_block;
    struct llist_data_object *next;
} llist_data_object_t;

static llist_data_object_t *llist_head = NULL;
static unsigned int llist_object_count = 0;

void *llist_getObject(unsigned int id, unsigned int size)
{
    llist_data_object_t *tmp = llist_head;
    while(tmp != NULL) {
        if ((tmp->id == id)) {
            if (tmp->data_length != size) break;
            return tmp->data_block;
        }
        tmp = tmp->next;
    }

    return NULL;
}


void *llist_createObject(unsigned int id, unsigned int size)
{
    llist_data_object_t *tmp = llist_head;
    llist_data_object_t *tmp2 = llist_head;
    int id_match = 0;
    while(tmp != NULL) {
        if ((tmp->id == id)) {
            id_match = 1;
            if (tmp->data_length != size) break;
            return tmp->data_block;
        }
        tmp2 = tmp;
        tmp = tmp->next;
    }


    if (!id_match) {
        tmp = (llist_data_object_t *)malloc(sizeof(llist_data_object_t));
        if (tmp != NULL) {
            tmp->id = id;
            tmp->data_length = size;
            tmp->next = NULL;
            tmp->data_block = (void *)malloc(size);
            if (tmp->data_block == NULL) {
                free(tmp);
                return NULL;
            }
            else {
                if (llist_head == NULL) llist_head = tmp;
                else tmp2->next = tmp;

                llist_object_count++;
                return tmp->data_block;
            }
        }
    }

    return NULL;
}

int llist_deleteObject(unsigned int id, unsigned int size)
{
    llist_data_object_t *tmp = llist_head;
    while(tmp != NULL) {
        if ((tmp->id == id)) {
            if (tmp->data_length != size) break;
            free(tmp->data_block);
            free(tmp);
            llist_object_count--;
            return 0;
        }
        tmp = tmp->next;
    }

    return -1;
}

unsigned int llist_getObjectCount(void)
{
    return llist_object_count;
}

