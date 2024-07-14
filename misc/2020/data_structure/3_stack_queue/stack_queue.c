/* stack, queue (array)
 * 20200128
 * init(), empty(), size(), push(), pop()
 * stack : top()
 * queue : front(), back()
 * 아래 코드는 generic하지 않은 stack, queue (반환값 돌려주는 pop()은 generic하지 않음)
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSZ 10

typedef struct {
    int key;
} Element;

Element EMPTY = {-1};

/* stack */

Element _stack[MAXSZ];
int _top = -1;

bool push(Element e)
{
    if (_top == MAXSZ - 1)
        return false;
    _stack[++_top] = e;
    return true;
}
Element pop()
{
    if (_top == -1)
        return EMPTY;
    return _stack[_top--];
}

/* queue */

Element _queue[MAXSZ];
int _front, _back;

bool enqueue(Element e)
{
    int tmp;
    tmp = (_back + 1) % MAXSZ;
    if (_front == tmp)
        return false;
    _queue[_back = tmp] = e;
    return true;
}
Element dequeue()
{
    if (_front == _back)
        return EMPTY;
    _front = (_front + 1) % MAXSZ;
    return _queue[_front];
}

/* main */

int main()
{
    int i;
    bool b;
    Element e;

    // stack test
    i = 0;
    while (true) {
        e.key = i++;
        b = push(e);
        if (b)
            printf("push %d\n", e.key);
        else
            break;
    }
    while (true) {
        e = pop();
        if (e.key != -1)
            printf("pop %d\n", e.key);
        else
            break;
    }

    // queue test
    i = 0;
    while (true) {
        e.key = i++;
        b = enqueue(e);
        if (b)
            printf("enqueue %d\n", e.key);
        else
            break;
    }
    while (true) {
        e = dequeue();
        if (e.key != -1)
            printf("dequeue %d\n", e.key);
        else
            break;
    }

    return 0;
}
