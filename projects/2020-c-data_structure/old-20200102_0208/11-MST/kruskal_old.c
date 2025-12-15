#include <stdio.h>
#include <stdlib.h>
#include "graph.c"

/* min heap */
#define MAXSZ 1000
Edge *heap[MAXSZ];
int n;
void push(Edge *e)
{
    int i;
    if (n == MAXSZ - 1)
        return;
    for (i = ++n; i > 1 && e->weight < heap[i/2]->weight; i /= 2)
        heap[i] = heap[i/2];
    heap[i] = e;
}
Edge *pop()
{
    int i;
    if (n == 0)
        return NULL;
    heap[0] = heap[1];
    Edge *e = heap[n--];
    for (i = 2; i <= n; i *= 2) {
        if (i + 1 <= n && heap[i]->weight > heap[i + 1]->weight)
            i++;
        if (e->weight > heap[i]->weight)
            heap[i/2] = heap[i];
        else
            break;
    }
    heap[i/2] = e;
    return heap[0];
}

/* Kruskal using array */
void _kruskal(Edge **multilist, int node_sz)
{
    int i;
    Edge *edge;
    int *union_find = malloc(node_sz * sizeof(*union_find));
    for (i = 0; i < node_sz; i++) {
        union_find[i] = i;  // make-set
        for (edge = multilist[i]; edge; edge = edge->path1)
            if (!edge->marked && edge->vertex1 < edge->vertex2) {
                edge->marked = true;
                push(edge);
            }
    }

    printf("Kruskal MST :");
    int k = 0, temp;
    while (k < node_sz - 1 && (edge = pop())) {
        if ((temp = union_find[edge->vertex2]) != union_find[edge->vertex1]) {
            printf(" <%d, %d>", edge->vertex1, edge->vertex2);
            for (i = 0; i < node_sz; i++)
                if (union_find[i] == temp)
                    union_find[i] = union_find[edge->vertex1];
            k++;
        }
    }
}

/* main */
#define MAX_VERTICES 7
int main(int argc, const char *argv[])
{
    Node *adjlist[MAX_VERTICES];
    adjlist[0] = set_node((2), 1, 28, 5, 10);
    adjlist[1] = set_node((3), 0, 28, 2, 16, 6, 14);
    adjlist[2] = set_node((2), 1, 16, 3, 12);
    adjlist[3] = set_node((3), 2, 12, 4, 22, 6, 18);
    adjlist[4] = set_node((3), 3, 22, 5, 25, 6, 24);
    adjlist[5] = set_node((2), 0, 10, 4, 25);
    adjlist[6] = set_node((3), 1, 14, 3, 18, 4, 24);

    Edge **multilist = nodes_to_edges(adjlist, MAX_VERTICES);
    _kruskal(multilist, MAX_VERTICES);
}