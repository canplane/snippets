#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define MAXSZ 100

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

#define INF 1000
int dist[MAXSZ], prev_weight[MAXSZ];
int pi[MAXSZ];
void print_path(int v)
{
    if (pi[v] != -1)
        print_path(pi[v]);
    printf("%d ", v);
}
bool belmanford(Node *adjlist[], int n, int v)  // O(|V||E|) = O(|V|^3)
{
    int i, w;
    for (i = 0; i < n; i++) {
        dist[i] = prev_weight[i] = INF;
        pi[i] = -1;
    }
    dist[v] = 0;
    for (i = 0; i < n - 1; i++) {
        for (w = 0; w < n; w++) {
            for (Node *node = adjlist[w]; node; node = node->link) {
                if (dist[w] < INF && dist[node->vertex] > dist[w] + node->weight) {
                    dist[node->vertex] = dist[w] + node->weight;
                    pi[node->vertex] = w;
                    prev_weight[node->vertex] = node->weight;
                }
            }
        }
    }
    for (w = 0; w < n; w++) {
        if (dist[w] > dist[pi[w]] + prev_weight[w]) {
            printf("Negative Cycle Detected\n");
            return false;
        }
    }
    for (i = 0; i < n; i++)
        if (i != v && dist[i] < INF) {
            print_path(i);
            printf(": %d\n", dist[i]);
        }
    return true;
}

/* main */
#define MAX_VERTICES 3
Node *adjlist[MAX_VERTICES];
int main()
{
    /*
    adjlist[0] = set_node((2), 1, 7, 2, 5);
    adjlist[1] = set_node((1), 2, -5);
    adjlist[2] = set_node((0));
     */
    adjlist[0] = set_node((1), 1, 1);
    adjlist[1] = set_node((2), 0, -2, 2, 1);
    adjlist[2] = set_node((0));

    belmanford(adjlist, MAX_VERTICES, 0);
}