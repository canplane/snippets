/* max heap
 * 20200201
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSZ 100

typedef struct {
    int key;
} Element;

Element _heap[MAXSZ];
int _size;

void push(Element e)
{
    int i;
    if (_size == MAXSZ - 1)
        return;
    for (i = ++_size; i > 1 && e.key > _heap[i/2].key; i /= 2)
        _heap[i] = _heap[i/2];
    _heap[i] = e;
}

void pop()
{
    int i;
    Element e;
    if (_size == 0)
        return;
    e = _heap[_size--];
    for (i = 2; i <= _size; i *= 2) {
        if (i + 1 <= _size && _heap[i+1].key > _heap[i].key)
            i++;
        if (_heap[i].key > e.key)
            _heap[i/2] = _heap[i];
        else
            break;
    }
    _heap[i/2] = e;
}

void init()
{
    _size = 0;
}
Element top()
{
    return _heap[1];
}
bool empty()
{
    return _size == 0;
}

/* main */

#define ARRSZ 6
int main()
{
    int i;
    int arr[ARRSZ] = {15, 4, 27, 9, 11, 6};
    Element e;
    for (i = 0; i < ARRSZ; i++)
        e.key = arr[i], push(e);
    while (!empty())
        printf("%d ", top().key), pop();
    return 0;
}