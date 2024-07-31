#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdbool.h>
#include "tree.h"

#define MAXSZ 100

Tree *_deque[MAXSZ];
int _front, _back;
void init() { _front = _back = 0; }
bool empty() { return _front == _back; }
Tree *front() { return _deque[(_front + 1) % MAXSZ]; }
Tree *back() { return _deque[_back]; }
void pushBack(Tree *e)
{
    int tmp;
    tmp = (_back + 1) % MAXSZ;
    if (tmp == _front) return;
    _deque[_back = tmp] = e;
}
void popBack()
{
    if (_front == _back) return;
    _back = (_back - 1) % MAXSZ;
}
void pushFront(Tree *e)
{
    int tmp;
    tmp = (_front - 1) % MAXSZ;
    if (tmp == _back) return;
    _deque[_front] = e;
    _front = tmp;
}
void popFront()
{
    if (_front == _back) return;
    _front = (_front + 1) % MAXSZ;
}

Tree *top() { return back(); }
void push(Tree *e) { pushBack(e); }
void pop() { popBack(); }
void enqueue(Tree *e) { pushBack(e); }
void dequeue() { popFront(); }

#endif