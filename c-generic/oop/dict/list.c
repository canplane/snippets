/* 
 * Generic list structure
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-11
 */


#ifndef __LIST__H
#define __LIST__H


#include <stdlib.h>
#include <string.h>
#include <string.h>


typedef struct ListNode { void *item; struct ListNode *next; } ListNode;
typedef struct List { ListNode *head, *tail; int size; } List;
#define ListNode__item(node, T) (*(T *)((node)->item))


List *new__List()
{
    List *li;
    li = malloc(sizeof(List)), memset(li, sizeof(List), 0);
    return li;
}


void List__push(List *li, void *item)
{
    li->size++;
    ListNode *node;
    node = malloc(sizeof(ListNode)), node->item = item;
    if (!li->head)
        li->head = li->tail = node;
    else
        li->tail = li->tail->next = node;
}


#endif