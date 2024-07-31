#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdbool.h>

#define DEQUE_MAX 100

static int _deque[DEQUE_MAX];
static int _front, _back;

void init()
{
    _front = _back = 0;
}
bool empty()
{
    return _front == _back;
}

int front()
{
    return _deque[(_front + 1) % DEQUE_MAX];
}
int back()
{
    return _deque[_back];
}
void pushFront(int e)
{
    int tmp;
    tmp = (_front - 1) % DEQUE_MAX;
    if (tmp == _back)
        return;
    _deque[_front] = e;
    _front = tmp;
}
void pushBack(int e)
{
    int tmp;
    tmp = (_back + 1) % DEQUE_MAX;
    if (tmp == _front)
        return;
    _deque[_back = tmp] = e;
}
void popFront()
{
    if (_front == _back)
        return;
    _front = (_front + 1) % DEQUE_MAX;
}
void popBack()
{
    if (_front == _back)
        return;
    _back = (_back - 1) % DEQUE_MAX;
}

#endif