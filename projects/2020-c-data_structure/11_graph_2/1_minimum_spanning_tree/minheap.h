#ifndef __MINHEAP_H__
#define __MINHEAP_H__

#include "../graph.h"
#define HEAP_MAX 100

static GraphEdge *_heap[HEAP_MAX];
static int _size;

typedef struct {
    GraphEdge *data[HEAP_MAX];
    int size;
} Heap;

void heap_init(Heap *heap)
{
    heap->size = 0;
}
void heap_push(Heap *heap, GraphEdge *e)
{
    int i;
    if (heap->size == HEAP_MAX - 1)
        return;
    for (i = ++heap->size; i > 1 && e->weight < heap->data[i/2]->weight; i /= 2)
        heap->data[i] = heap->data[i/2];
    heap->data[i] = e;
}
GraphEdge *heap_pop(Heap *heap)
{
    int i;
    GraphEdge *e;
    if (heap->size == 0)
        return NULL;
    heap->data[0] = heap->data[1];
    e = heap->data[heap->size--];
    for (i = 2; i <= heap->size; i *= 2) {
        if (i + 1 <= heap->size && heap->data[i + 1]->weight < heap->data[i]->weight)
            i++;
        if (heap->data[i]->weight < e->weight)
            heap->data[i/2] = heap->data[i];
        else
            break;
    }
    heap->data[i/2] = e;
    return heap->data[0];
}

#endif