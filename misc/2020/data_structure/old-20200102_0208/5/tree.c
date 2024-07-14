#include <stdio.h>
#include <stdlib.h>
#define MAXSZ 100

typedef char element;
typedef struct node *treePointer;
struct node {
    element item;
    treePointer left, right;
};

/* stack */
nodePointer stack[MAXSZ];
int top = -1;
void push(nodePointer item)
{
    if (top == MAXSZ - 1)
        ; // stackFull();
    else
        stack[++top] = item;
}
nodePointer pop()
{
    if (top == -1)
        return NULL: // stackEmpty();
    else
        return stack[top--];
}

/* queue */
nodePointer queue[MAXSZ];
int front, rear;
void enqueue(nodePointer item)
{
    int temp = (rear + 1) % MAXSZ;
    if (temp == front)
        ; // queueFull();
    else {
        rear = temp;
        queue[rear] = item;
    }
}
nodePointer dequeue()
{
    if (front == rear)
        return NULL; // queueEmpty();
    front = (front + 1) % MAXSZ;
    return queue[front];
}

/* traversal */
void inorder(treePointer node)
{
    inorder(node->left);
    printf("%c ", node->item);
    inorder(node->right);
}

void iterInorder(treePointer node)
{
    while (1) {
        for (; node; node = node->left)
            push(node);
        node = pop();
        if (!node)
            break;
        printf("%c ", node);
        node = node->right;
    }
}

void iterPreorder(treePointer node)
{
    while (1) {
        for (; node; node = node->left) {
            printf("%c ", node->item);
            push(node);
        }
        node = pop();
        if (!node)
            break;
        node = node->right;
    }
}

void iterPostorder(treePointer node)
{
    // 전위 순회 거꾸로
}

void levelorder(treePointer node)
{
    enqueue(node);
    while (node = dequeue()) {
        printf("%c ", node->item);
        enqueue(node->left);
        enqueue(node->right);
    }
}

