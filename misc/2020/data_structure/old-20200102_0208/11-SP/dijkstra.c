#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {false, true} bool;

typedef struct node {
    int vertex;
    int weight;
    struct node *link;
} Node;

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

/* Dijkstra */
unsigned int distance[MAX_VERTICES];
bool found[MAX_VERTICES];
int pi[MAX_VERTICES];

void print_path(int v)
{
    if (pi[v] != -1)
        print_path(pi[v]);
    printf("%d ", v);
}

void dijkstra(Node *adjlist[], int n, int v)    // O(|V| * (|V| + |E|/|V|)) = O(|V|^2)
{
    int i;
    for (i = 0; i < n; i++) {
        distance[i] = -1U;
        pi[i] = -1;
        found[i] = false;
    }
    distance[v] = 0;
    
    while (true) { // 최대 n-1번
        for (Node *node = adjlist[v]; node; node = node->link) {
            if (!found[node->vertex] && distance[node->vertex] > distance[v] + node->weight) {
                distance[node->vertex] = distance[v] + node->weight;    // edge relaxation
                pi[node->vertex] = v;
            }
        }
        found[v] = true;
        v = -1;
        for (i = 0; i < n; i++) {
            if (!found[i] && (v == -1 || distance[i] < distance[v]))
                v = i;
        }
        if (v == -1 || distance[v] == -1)
            break;
        print_path(v);
        printf(": %d\n", distance[v]);
    }
}

/* main */
#define MAX_VERTICES 6
Node *adjlist[MAX_VERTICES];
int main()
{
    adjlist[0] = set_node((3), 1, 50, 2, 10, 4, 45);
    adjlist[1] = set_node((2), 2, 15, 4, 10);
    adjlist[2] = set_node((2), 0, 20, 3, 15);
    adjlist[3] = set_node((2), 1, 20, 4, 35);
    adjlist[4] = set_node((1), 3, 30);
    adjlist[5] = set_node((1), 3);

    dijkstra(adjlist, MAX_VERTICES, 0);
}