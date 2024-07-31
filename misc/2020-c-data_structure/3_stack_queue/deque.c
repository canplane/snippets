/* deque (array)
 * 20200129
 * init(), empty(), size(), pushBack(), popFront(), pushFront(), popBack(), front(), back()
 * circular이므로 MAXSZ - 1개 데이터만큼만 넣을 수 있음 
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSZ 10

typedef struct {
    int key;
} Element;

Element _deque[MAXSZ];
int _front, _back, _size;

void init()
{
    _front = _back = _size = 0;
}
bool empty()
{
    return _front == _back;
}
int size()
{
    return _size;
}
void pushBack(Element e)
{
    int tmp;
    tmp = (_back + 1) % MAXSZ;
    if (tmp == _front)
        return;
    _size++;
    _deque[_back = tmp] = e;
}
void popFront()
{
    if (_front == _back)
        return;
    _size--;
    _front = (_front + 1) % MAXSZ;
}
void pushFront(Element e)
{
    int tmp;
    tmp = (_front - 1) % MAXSZ;
    if (tmp == _back)
        return;
    _size++;
    _deque[_front] = e;     // 주의
    _front = tmp;
}
void popBack()
{
    if (_front == _back)
        return;
    _size--;
    _back = (_back - 1) % MAXSZ;
}
Element front()
{
    return _deque[(_front + 1) % MAXSZ];
}
Element back()
{
    return _deque[_back];
}

void printDeque()
{
    int i;
    if (_front < _back) {
        for (i = 0; i <= _front; i++)
            printf(".");
        for (; i <= _back; i++)
            printf("%d", _deque[i].key);
        for (; i < MAXSZ; i++)
            printf(".");
    }
    else if (_back < _front) {
        for (i = 0; i <= _back; i++)
            printf("%d", _deque[i].key);
        for (; i <= _front; i++)
            printf(".");
        for (; i < MAXSZ; i++)
            printf("%d", _deque[i].key);
    }
    else
        for (i = 0; i < MAXSZ; i++)
            printf(".");
    
    printf("    front : %d, back : %d, size : %d", _front, _back, size());
    printf("\n");
}

/* main */

int main()
{
    int i;
    Element e;

    // deque test
    printf("deque test --------\n");
    init();
    // pushBack = enqueue
    for (i = 0; i < MAXSZ - 1; i++) {
        e.key = i;
        pushBack(e);
        printf("pushBack %d     ", e.key);
        printDeque();
    }
    // pushFront = pop, dequeue
    while (!empty()) {
        e = front();
        popFront();
        printf("popFront %d     ", e.key);
        printDeque();
    }
    // pushFront = push
    for (i = 0; i < MAXSZ - 1; i++) {
        e.key = i;
        pushFront(e);
        printf("pushFront %d    ", e.key);
        printDeque();
    }
    // popBack
    while (!empty()) {
        e = back();
        popBack();
        printf("popBack %d      ", e.key);
        printDeque();
    }

    return 0;
}
