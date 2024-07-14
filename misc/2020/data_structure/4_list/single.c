/* singly linked list
 * 20200129
 * insert(), delete()
 * insert()시 head, tail 갱신 가능, delete()시 tail은 불가능 (popBack() 구현하려면 doubly)
 * insert()는 doubly linked list에서 소거, delete()는 별개로 구현
 * 양방향이 아니므로 간이 구현에 초점 맞추고 delete()는 void 반환
 * 포인터는 웬만해서는 처음에 NULL로 초기화하자.
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

Node *insert(Node **head, Node *left, Element e)
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
void delete(Node **node)
{
    Node *tmp;
    tmp = *node;
    *node = tmp->next;
    free(tmp);
}

void printList(Node *head)
{
    for (; head; head = head->next)
        printf("%d ", head->item.key);
    printf("\n");
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
        insert(&head, NULL, e);
        printList(head);
    }
    // pop
    printf("pop :\n");
    while (head) {
        delete(&head);
        printList(head);
    }

    // queue test
    printf("queue test --------\n");
    head = tail = NULL;
    // enqueue
    printf("enqueue :\n");
    for (i = 0; i < MAXSZ; i++) {
        e.key = i;
        tail = insert(&head, tail, e);
        printList(head);
    }
    // dequeue
    printf("dequeue :\n");
    while (head) {
        delete(&head);
        printList(head);
    }

    return 0;
}

