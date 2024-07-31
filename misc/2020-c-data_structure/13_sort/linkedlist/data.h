#ifndef __ELEMENT_H__
#define __ELEMENT_H__
typedef struct {
    int key;
} Element;
#endif

#include <stdio.h>
#include <stdarg.h>
#include "list.h"

void setData(List *list, int size, ...)
{
    Element e;
    Node *node;
    va_list ap;
    int key;
    va_start(ap, size);

    list->head = list->tail = NULL;
    while (size--) {
        e.key = va_arg(ap, int);
        list_insert(list, list->tail, e);
    }
    va_end(ap);
}

void printData(List *list)
{
    Node *node;
    for (node = list->head; node; node = node->next)
        printf("%d ", node->item.key);
    printf("\n");
}
