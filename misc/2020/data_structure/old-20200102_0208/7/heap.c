#include <stdlib.h>

typedef enum {false, true} bool;

#define MAXSZ 100
typedef struct {
    int key;
} *element_t;

element_t heap[MAXSZ];
int n;

bool push(element_t e)
{
    int i;
    if (n == MAXSZ - 1)
        return false; // full
    for (i = ++n; i > 1 && e->key > heap[i/2]->key; i /= 2)
        heap[i] = heap[i/2];
    heap[i] = e;
    return true;
}

element_t pop()
{
    int i;
    element_t item;
    if (n == 0)
        return NULL; // empty
    heap[0] = heap[1];
    item = heap[n--];
    for (i = 2; i <= n; i *= 2) {
        if (i + 1 <= n && heap[i + 1]->key > heap[i]->key)
            i++;
        if (item->key < heap[i]->key)
            heap[i/2] = heap[i];
        else
            break;
    }
    heap[i/2] = item;
    return heap[0];
}

///
#include <stdio.h>

element_t new_Element(int key)
{
    element_t e = (element_t)malloc(sizeof(*e));
    e->key = key;
    return e;
}

int main()
{
    element_t e;
    push(new_Element(26));
    push(new_Element(5));
    push(new_Element(37));
    push(new_Element(1));
    push(new_Element(61));
    push(new_Element(11));
    push(new_Element(59));
    push(new_Element(15));
    push(new_Element(48));
    push(new_Element(19));
    while (e = pop())
        printf("%d ", e->key);
    printf("\n");
}
