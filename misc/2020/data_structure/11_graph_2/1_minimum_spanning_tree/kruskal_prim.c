/* Kruskal, Prim's algorithm
 * 20200203
 * spanning tree는 undirected graph 대상
 * Prim은 disjoint set을 visited로 대체해도 됨 (marked는 안 씀) 그런데 MST 자료 구조 반환할 것이므로 disjoint set 기반한 게 좋음
 * 모두 edge에 대한 heap 필요. adjacency list -> multilist로 변환하는 함수 만들기보다는 필요할 때마다 개별로 변환해서 heap에 push하는 방법이 더 편함. (multilist에서 path 연결할 필요 없음)
 * forest.h : MST 자료 구조로 이용하기 위해 기존의 disjoint set 알고리즘 변형. 단, unrooted tree에서 임의 노드를 root로 삼는 disjoint set 반환
 * MST 자료구조 형성에는 Prim이 좋을 것 (다른 알고리즘은 forest를 사용하므로 병합 시 구조를 변경해야 할 경우가 많음)
 */

#include <stdio.h>
#include <stdbool.h>
#include "../graph.h"
#include "forest.c"     // disjoint set 알고리즘 변형
#include "minheap.h"

void kruskal(GraphNode *adjLists[], int parent[], int size)
{
    int i;
    GraphNode *node;
    GraphEdge *edge;
    int T[size - 1][2];
    
    Heap heap;
    heap_init(&heap), forest_init(parent, size);

    for (i = 0; i < size; i++) {    // 처음에 모두 heap에 넣는다
        for (node = adjLists[i]; node; node = node->link) {
            if (i < node->vertex) {
                edge = malloc(sizeof(GraphEdge));
                edge->vertex1 = i, edge->vertex2 = node->vertex;
                edge->weight = node->weight;
                heap_push(&heap, edge);
            }
        }
    }
    i = 0;
    while (i < size - 1 && (edge = heap_pop(&heap))) {
        if (forest_find(parent, edge->vertex1) != forest_find(parent, edge->vertex2)) { // cycle 확인
            T[i][0] = edge->vertex1, T[i][1] = edge->vertex2;
            forest_union(parent, edge->vertex1, edge->vertex2);
            i++;
        }
    }

    printf("Kruskal MST : ");
    if (i != size - 1) {
        printf("no spanning tree\n");
        return;
    }
    printf("T = {");
    for (i = 0; i < size - 1; i++)
        printf("(%d,%d)", T[i][0], T[i][1]);
    printf("}\n");
}

void prim(GraphNode *adjLists[], int parent[], int size, int v)
{
    int i;
    GraphNode *node;
    GraphEdge *edge;
    int TV[size], T[size - 1][2];

    Heap heap;
    heap_init(&heap), forest_init(parent, size);

    TV[0] = v;
    for (i = 0; i < size - 1; i++) {
        v = TV[i];
        for (node = adjLists[v]; node; node = node->link) { // 확장될 때마다 heap에 넣는다
            edge = malloc(sizeof(GraphEdge));
            edge->vertex1 = v, edge->vertex2 = node->vertex;
            edge->weight = node->weight;
            heap_push(&heap, edge);
        }
        while ((edge = heap_pop(&heap)) && forest_find(parent, edge->vertex1) == forest_find(parent, edge->vertex2));
        if (!edge)
            break;
        T[i][0] = edge->vertex1, T[i][1] = TV[i + 1] = edge->vertex2;
        forest_union(parent, edge->vertex1, edge->vertex2);
    }

    printf("Prim MST : ");
    if (i != size - 1) {
        printf("no spanning tree\n");
        return;
    }
    printf("TV = { ");
    for (i = 0; i < size; i++)
        printf("%d ", TV[i]);
    printf("}, T = {");
    for (i = 0; i < size - 1; i++)
        printf("(%d,%d)", T[i][0], T[i][1]);
    printf("}\n");
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

    kruskal(adjLists, forest, MAX_VERTICES);
    printf("forest : ");
    for (i = 0; i < MAX_VERTICES; i++)
        printf("%d ", forest[i]);
    printf("\n");

    prim(adjLists, forest, MAX_VERTICES, 0);
    printf("forest : ");
    for (i = 0; i < MAX_VERTICES; i++)
        printf("%d ", forest[i]);
    printf("\n");

    return 0;
}