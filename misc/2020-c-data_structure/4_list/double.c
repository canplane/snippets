/* doubly linked list
 * 20200129
 * List, init(), empty(), insert(), delete()
 * insert()는 일단 좌우 연결하고 좌우에서 다시 노드 돌아오기, delete()는 좌우 찾고 서로 연결
 * insert()는 왼쪽 노드 파라미터로 받고 생성 노드 반환(dequeue()에 필요한 tail로 쓸 수 있음), delete()는 대상 노드 파라미터로 받고 왼쪽 노드 반환
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
Node *insert(List *list, Node *left, Element e)
{
    Node *right;
    Node *node;
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
Node *delete(List *list, Node *node)
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

    // stack test
    printf("stack test --------\n");
    // push
    printf("push :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        insert(&list, NULL, e);
        printList(&list);
        //printRList(&list);
    }
    // pop
    printf("pop :\n");
    while (!empty(&list)) {
        delete(&list, list.head);
        printList(&list);
        //printRList(&list);
    }

    // queue test
    printf("queue test --------\n");
    // enqueue
    printf("enqueue :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        insert(&list, list.tail, e);
        printList(&list);
        //printRList(&list);
    }
    // dequeue
    printf("dequeue :\n");
    while (!empty(&list)) {
        delete(&list, list.head);
        printList(&list);
        //printRList(&list);
    }

    // deque test
    printf("deque test --------\n");
    // pushFront
    printf("pushFront :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        insert(&list, NULL, e);
        printList(&list);
        //printRList(&list);
    }
    // popBack
    printf("popBack :\n");
    while (!empty(&list)) {
        delete(&list, list.tail);
        printList(&list);
        //printRList(&list);
    }

    return 0;
}