#ifndef __ELEMENT_H__
#include "data.h"
#endif

#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node {
    Element item;
    struct node *prev, *next;
} Node;

typedef struct {
    Node *head, *tail;
} List;

Node *list_insert(List *list, Node *left, Element e)
{
    Node *node;
    Node *right;
    node = malloc(sizeof(Node));
    node->item = e;
    right = left ? left->next : list->head;
    node->prev = left, node->next = right;
    if (left)
        left->next = node;
    else
        list->head = node;
    if (right)
        right->prev = node;
    else
        list->tail = node;
    return node;
}
Node *list_delete(List *list, Node *node)
{
    Node *left, *right;
    left = node->prev, right = node->next;
    if (left)
        left->next = right;
    else
        list->head = right;
    if (right)
        right->prev = left;
    else
        list->tail = left;
    free(node);
    return left;
}

void list_transplant(List *list, Node *dstLeft, Node *node)
{
    Node *left, *right;

    left = node->prev, right = node->next;
    if (left)
        left->next = right;
    else
        list->head = right;
    if (right)
        right->prev = left;
    else
        list->tail = left;
    
    left = dstLeft;
    right = left ? left->next : list->head;
    node->prev = left, node->next = right;
    if (left)
        left->next = node;
    else
        list->head = node;
    if (right)
        right->prev = node;
    else
        list->tail = node;
}

#endif
