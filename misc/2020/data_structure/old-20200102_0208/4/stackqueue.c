#include <stdio.h>

/* _malloc */
#define malloc(sz) _malloc(sz)
#define free(p)
#define LOCSZ 1000000000000L
char loc[LOCSZ], *p = loc;
void *_malloc(unsigned int sz) { return p += sz; }

typedef int Element;
#define EMPTY -1

typedef struct node {
    Element item;
    struct node *link;
} Node;

/* stack */
typedef struct {
    Node *top;
} Stack;

void push(Stack *stack, Element e)
{
    Node *node = malloc(sizeof(*node));
    node->item = e;
    node->link = stack->top;
    stack->top = node;
}

Element pop(Stack *stack)
{
    Element e;
    Node *node = stack->top;
    if (!node)
        return EMPTY;
    stack->top = node->link;
    e = node->item;
    free(node);
    return e;
}

/* queue : front가 NULL이면 rear는 볼 필요도 없음 */
typedef struct {
    Node *front;
    Node *rear;    
} Queue;

void enqueue(Queue *queue, Element e)
{
    Node *node = malloc(sizeof(*node));
    node->item = e;
    node->link = NULL;
    if (queue->front)
        queue->rear->link = node;
    else
        queue->front = node;
    queue->rear = node;
}

Element dequeue(Queue *queue)
{
    Element e;
    Node *node = queue->front;
    if (!node)
        return EMPTY;
    queue->front = node->link;
    e = node->item;
    free(node);
    return e;
}

/* main */

int main()
{
    Element e;

    Stack stack = {0, };
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    while ((e = pop(&stack)) != EMPTY)
        printf("%d ", e);
    push(&stack, 4);
    push(&stack, 5);
    push(&stack, 6);
    while ((e = pop(&stack)) != EMPTY)
        printf("%d ", e);
    printf("\n");

    Queue queue = {0, };
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    while ((e = dequeue(&queue)) != EMPTY)
        printf("%d ", e);
    enqueue(&queue, 4);
    enqueue(&queue, 5);
    enqueue(&queue, 6);
    while ((e = dequeue(&queue)) != EMPTY)
        printf("%d ", e);
    printf("\n");
}