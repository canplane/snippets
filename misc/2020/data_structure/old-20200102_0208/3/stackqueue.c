#define MAXSZ 100

/* stack */
element stack[MAXSZ];
int top = -1;

void push(element e)
{
    if (top == MAXSZ - 1)
        return;
    stack[++top] = e;
}

element pop()
{
    if (top == -1)
        return empty();
    return stack[top--];
}

/* queue */
element queue[MAXSZ];
int front, rear;

void enqueue(element e)
{
    int temp = (rear + 1) % MAXSZ; 
    if (temp == front)
        return;
    queue[rear = temp] = e;
}

element dequeue()
{
    if (front == rear)
        return empty();
    front = (front + 1) % MAXSZ;
    return queue[front];
}