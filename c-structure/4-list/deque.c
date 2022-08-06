/* deque (doubly linked list)
 * 20200129
 * init(), empty(), size(), pushFront(), pushBack(), popFront(), popBack()
 * doubly linked list에서 소거해서 만들기
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
} Element;

typedef struct node {
    Element item;
    struct node *prev, *next;
} Node;

typedef struct {
    Node *head, *tail;
} List;

void init(List *list)
{
    list->head = list->tail = NULL;
}
bool empty(List *list)
{
    return !list->head;
}
void pushFront(List *list, Element e)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->item = e;
    
    node->prev = NULL;
    node->next = list->head;
    if (list->head)
        list->head->prev = node;
    else
        list->tail = node;
    list->head = node;
}
void pushBack(List *list, Element e)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->item = e;

    node->prev = list->tail;
    node->next = NULL;
    if (list->tail)
        list->tail->next = node;
    else
        list->head = node;
    list->tail = node;
}
void popFront(List *list)
{
    Node *node;
    node = list->head;

    if (node->next)
        node->next->prev = NULL;
    else
        list->tail = NULL;
    list->head = node->next;

    free(node);
}
void popBack(List *list)
{
    Node *node;
    node = list->tail;

    if (node->prev)
        node->prev->next = NULL;
    else
        list->head = NULL;
    list->tail = node->prev;

    free(node);
}

void printList(List *list)
{
    Node *node;
    //printf("print from head : ");
    for (node = list->head; node; node = node->next)
        printf("%d ", node->item.key);
    printf("\n");
}
void printRList(List *list)
{
    Node *node;
    //printf("print from tail : ");
    for (node = list->tail; node; node = node->prev)
        printf("%d ", node->item.key);
    printf("\n");
}

/* main */

#define MAXSZ 10
int main()
{
    int i;
    Element e;
    List list;
    init(&list);

    // deque test
    printf("deque test --------\n");
    // pushBack = enqueue
    printf("pushBack :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        pushBack(&list, e);
        printList(&list);
        //printRList(&list);
    }
    // pushFront = pop, dequeue
    printf("popFront :\n");
    while (!empty(&list)) {
        popFront(&list);
        printList(&list);
        //printRList(&list);
    }
    // pushFront = push
    printf("pushFront :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        pushFront(&list, e);
        printList(&list);
        //printRList(&list);
    }
    // popBack
    printf("popBack :\n");
    while (!empty(&list)) {
        popBack(&list);
        printList(&list);
        //printRList(&list);
    }

    return 0;
}