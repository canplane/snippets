/* Sollin's algorithm
 * 20200205
 * 각 node에 대한 heap 배열 형성, union 연산 취할 때마다 heap도 병합
 * 각 node에 대한 heap 배열 만들고 한 개 node를 고정해서 확장해 나간다면 Prim이라 볼 수 있음
 */

#include <stdio.h>
#include <stdbool.h>
#include "../graph.h"
#include "forest.c"
#include "minheap.h"

void sollin(GraphNode *adjLists[], int parent[], int size)
{
    int i, j, tmp;
    bool changed;
    GraphNode *node;
    GraphEdge *edge;
    int count;

    Heap heaps[size];

    for (i = 0; i < size; i++) {
        heap_init(&heaps[i]);
        for (node = adjLists[i]; node; node = node->link) {
            edge = malloc(sizeof(GraphEdge));
            edge->vertex1 = i, edge->vertex2 = node->vertex;
            edge->weight = node->weight;
            heap_push(&heaps[i], edge);
        }
    }

    printf("Sollin MST : \n");
    forest_init(parent, size);
    count = 0;
    do {
        printf("stage %d : ", ++count);
        changed = false;
        for (i = 0; i < size; i++) {
            while ((edge = heap_pop(&heaps[i])) && i == (j = forest_find(parent, edge->vertex2)));
            if (!edge)
                continue;
            changed = true;
            printf("(%d,%d)", edge->vertex1, edge->vertex2);
            forest_union(parent, edge->vertex1, edge->vertex2); // i 트리(vertex1)에 j 트리(vertex2) 추가하고 j 힙 모두 이동
            while (edge = heap_pop(&heaps[j]))
                heap_push(&heaps[i], edge);
        }
        printf("\n");
    } while (changed);

    tmp = -1;
    for (i = 0; i < size; i++) {
        if (parent[i] < 0) {
            if (tmp != -1) {    // 루트가 두 개 이상 존재
                printf("no spanning tree\n");
                return;
            }
            tmp = i;
        }
    }
}

/* main */

#define MAX_VERTICES 7
int main()
{
    int i;
    GraphNode *adjLists[] = {
        newNode((2), 1, 28, 5, 10),
        newNode((3), 0, 28, 2, 16, 6, 14),
        newNode((2), 1, 16, 3, 12),
        newNode((3), 2, 12, 4, 22, 6, 18),
        newNode((3), 3, 22, 5, 25, 6, 24),
        newNode((2), 0, 10, 4, 25),
        newNode((3), 1, 14, 3, 18, 4, 24)
    };
    int forest[MAX_VERTICES];

    sollin(adjLists, forest, MAX_VERTICES);
    printf("forest : ");
    for (i = 0; i < MAX_VERTICES; i++)
        printf("%d ", forest[i]);
    printf("\n");

    return 0;
}
