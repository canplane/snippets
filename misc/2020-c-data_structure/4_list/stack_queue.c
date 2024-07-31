/* stack, queue (singly linked list)
 * 20200129
 * doubly linked list에서 소거해서 만들기
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} Element;

typedef struct node {
    Element item;
    struct node *next;
} Node;

void printList(Node *head)
{
    for (; head; head = head->next)
        printf("%d ", head->item.key);
    printf("\n");
}

/* stack : top = head */

void push(Node **head, Element e)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->item = e;
    
    node->next = *head;
    *head = node;
}
void pop(Node **head)
{
    Node *tmp;
    tmp = *head;
    *head = tmp->next;
    free(tmp);
}

/* queue : (front, rear) = (head, tail) */

void enqueue(Node **head, Node **tail, Element e)
{
    Node *node;
    node = malloc(sizeof(Node));
    node->item = e;

    node->next = NULL;
    if (*tail)
        (*tail)->next = node;
    else
        *head = node;
    *tail = node;
}
void dequeue(Node **head, Node **tail)
{
    Node *tmp;
    tmp = *head;

    if (!(*head)->next)
        *tail = NULL;
    *head = (*head)->next;
    free(tmp);
}

/* main */

#define MAXSZ 10
int main()
{
    int i;
    Element e;
    Node *head, *tail;

    // stack test
    printf("stack test --------\n");
    head = NULL;
    // push
    printf("push :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        push(&head, e);
        printList(head);
    }
    // pop
    printf("pop :\n");
    while (head) {
        pop(&head);
        printList(head);
    }

    // queue test
    printf("queue test --------\n");
    head = tail = NULL;
    // enqueue
    printf("enqueue :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        enqueue(&head, &tail, e);
        printList(head);
    }
    // dequeue
    printf("dequeue :\n");
    while (head) {
        dequeue(&head, &tail);
        printList(head);
    }

    return 0;
}