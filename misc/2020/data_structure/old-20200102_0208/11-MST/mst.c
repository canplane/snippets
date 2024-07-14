#include <stdio.h>
#include "graph.c"
#include "min_heap.c"
#include "union_find.c"

/* Kruskal */
void kruskal(Node *adjlist[], int node_sz)
{
    int i;
    Edge *edge;
    for (i = 0; i < node_sz; i++) {
        for (Node *node = adjlist[i]; node; node = node->link) {
            if (i < node->vertex) {
                edge = malloc(sizeof(*edge));
                edge->marked = false;
                edge->vertex1 = i;
                edge->vertex2 = node->vertex;
                edge->weight = node->weight;
                push(edge);
            }
        }
    }

    printf("Kruskal MST :");
    int k = 0;
    _make_set(node_sz);
    while (k < node_sz - 1 && (edge = pop())) {
        if (_find(edge->vertex1) != _find(edge->vertex2)) {
            printf(" <%d, %d>", edge->vertex1, edge->vertex2);
            _union(edge->vertex1, edge->vertex2);
            k++;
        }
    }
    if (k != node_sz - 1)
        printf(" : No Spanning Tree\n");
}

/* Prim */
void prim(Node *adjlist[], int node_sz)
{
    int i, k;
    Edge *edge;
    printf("Prim MST :");
    bool *visited = malloc(node_sz * sizeof(*visited));
    memset(visited, 0, node_sz * sizeof(*visited));
    i = 0, k = 0;
    while (k < node_sz - 1) {
        visited[i] = true;
        for (Node *node = adjlist[i]; node; node = node->link) {
            if (!visited[node->vertex]) { // if 안 달아도 됨
                edge = malloc(sizeof(*edge));
                edge->vertex1 = i;
                edge->vertex2 = node->vertex;
                edge->weight = node->weight;
                push(edge);
            }
        }
        while (edge = pop()) {
            if (!visited[edge->vertex2]) {
                printf(" <%d, %d>", edge->vertex1, edge->vertex2);
                k++;
                i = edge->vertex2;
                break;
            }
        }
        if (!edge)
            break;
    }
    if (k != node_sz - 1)
        printf(" : No Spanning Tree\n");
}
