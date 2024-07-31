#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

/* adjlist */
typedef struct node {
    int vertex;
    int weight;
    struct node *link;
} Node;

#include <stdarg.h>
Node *_set_node(int argc, va_list ap)
{
    Node *node = NULL;
    if (argc) {
        node = malloc(sizeof(*node));
        node->vertex = va_arg(ap, int);
        node->weight = va_arg(ap, int);
        node->link = _set_node(--argc, ap);
    }
    return node;
}
Node *set_node(int argc, ...)
{
    Node *node;
    va_list ap;
    va_start(ap, argc);
    node = _set_node(argc, ap);
    va_end(ap);
    return node;
}

/* multilist */
typedef struct edge {
    bool marked;
    int vertex1, vertex2;
    int weight;
    struct edge *path1, *path2;
} Edge;

/*
Edge **nodes_to_edges(Node **adjlist, int node_sz)
{
    Edge **multilist, *edge;
    int adj;
    multilist = malloc(node_sz * sizeof(*multilist));
    memset(multilist, 0, node_sz * sizeof(*multilist));
    for (int i = 0; i < node_sz; i++) {
        for (Node *node = adjlist[i]; node; node = node->link) {
            if ((adj = node->vertex) > i) { // for undirected graphs
                edge = malloc(sizeof(*edge));
                edge->marked = false;
                edge->vertex1 = i;
                edge->vertex2 = node->vertex;
                edge->weight = node->weight;
                edge->path1 = multilist[i];
                edge->path2 = multilist[node->vertex];
                multilist[i] = multilist[node->vertex] = edge;
            }
        }
    }
    return multilist;
}
*/
