#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

#define ITEMTYPE int

typedef struct node {
    ITEMTYPE item;
    struct node *next;
} Node;

Node *list_insert(Node **head, Node *left, ITEMTYPE e)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->item = e;

    node->next = left ? left->next : *head;
    if (left)
        left->next = node;
    else
        *head = node;
    
    return node;
}
void list_delete(Node **node)
{
    Node *tmp;
    tmp = *node;
    *node = tmp->next;
    free(tmp);
}

#endif