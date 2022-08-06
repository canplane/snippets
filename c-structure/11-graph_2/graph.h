#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

/* adjacency list (node) */

typedef struct graphNode {
    int vertex;
    int weight;
    struct graphNode *link;
} GraphNode;

static GraphNode *_newNode(int argc, va_list ap)
{
    GraphNode *node = NULL;
    if (argc) {
        node = malloc(sizeof(GraphNode));
        node->vertex = va_arg(ap, int);
        node->weight = va_arg(ap, int);
        node->link = _newNode(--argc, ap);
    }
    return node;
}
GraphNode *newNode(int argc, ...)
{
    GraphNode *node;
    va_list ap;
    va_start(ap, argc);
    node = _newNode(argc, ap);
    va_end(ap);
    return node;
}

/* adjacency multilist (edge) */

typedef struct graphEdge {
    // bool marked;
    int vertex1, vertex2;
    int weight;
    // struct graphEdge *path1, *path2;
} GraphEdge;

/*
void nodeToEdge(GraphEdge *multilists[], GraphNode *adjLists[], int size)
{
    int v, w;
    GraphNode *node;
    GraphEdge *edge;
    for (v = 0; v < size; v++)
        multilists[v] = NULL;
    for (v = 0; v < size; v++) {
        for (node = adjLists[v]; node; node = node->link) {
            w = node->vertex;
            if (v <= w) {
                edge = malloc(sizeof(GraphEdge));
                edge->vertex1 = v, edge->vertex2 = w;
                edge->weight = node->weight;
                edge->path1 = multilists[v], edge->path2 = multilists[w];
                multilists[v] = multilists[w] = edge;
            }
        }
    }
}
*/

#endif