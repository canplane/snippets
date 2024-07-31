/* dfs, bfs, spanning tree, connected components
 * articulation points, biconnected components
 * 20200203
 * undirected graph 대상
 */

#include <stdio.h>
#include <stdbool.h>
#include "graph.c"
#include "deque.h"

#define MIN2(x, y) ((x) < (y) ? (x) : (y))
#define MAXSZ 10

static bool visited[MAXSZ];

void visited_init(int size)
{
    while (--size + 1)
        visited[size] = 0;
}

/* traversal */

void dfs(GraphNode *adjLists[], int v)
{
    GraphNode *node;
    visited[v] = true;
    printf("%3d", v);
    for (node = adjLists[v]; node; node = node->link) {
        if (!visited[node->vertex])
            dfs(adjLists, node->vertex);
    }
}

void bfs(GraphNode *adjLists[], int v)
{
    GraphNode *node;
    visited[v] = true;
    pushBack(v); // enqueue
    while (true) {
        if (empty())
            break;
        v = front(), popFront(); // dequeue
        printf("%3d", v);
        for (node = adjLists[v]; node; node = node->link) {
            v = node->vertex;
            if (!visited[v]) {
                visited[v] = true;
                pushBack(v); // enqueue
            }
        }
    }
}

/* dfs spanning tree (disjoint set), connected components */

// using disjoint set
void dfst(GraphNode *adjLists[], int parent[], int v, int u) // u -> v
{
    GraphNode *node;
    visited[v] = true;
    parent[v] = u;
    for (node = adjLists[v]; node; node = node->link) {
        if (!visited[node->vertex])
            dfst(adjLists, parent, node->vertex, v);
    }
}
// using directed graph
void dfst2(GraphNode *adjLists[], GraphNode *trees[], int v)
{
    int w;
    GraphNode *node, *child;
    visited[v] = true;
    for (node = adjLists[v]; node; node = node->link) {
        w = node->vertex;
        if (!visited[w]) {
            child = malloc(sizeof(GraphNode));
            child->vertex = w;
            child->link = trees[v];
            trees[v] = child;
            dfst2(adjLists, trees, w);
        }
    }
}

void connected(GraphNode *adjLists[], int size)
{
    int v;
    for (v = 0; v < size; v++) {
        if (!visited[v]) {
            printf("new connected component : ");
            dfs(adjLists, v);
            printf("\n");
        }
    }
}

/* biconnected components, articulation points */

static int dfn[MAXSZ], low[MAXSZ], next_dfn;
void dfnlow_init(int size)
{
    next_dfn = 0;
    while (--size + 1)
        low[size] = dfn[size] = -1;
}

void dfnlow(GraphNode *adjLists[], int v, int u)
{
    GraphNode *node;
    int w;
    low[v] = dfn[v] = next_dfn++;
    for (node = adjLists[v]; node; node = node->link) {
        w = node->vertex;
        if (dfn[w] == -1) {     // child
            dfnlow(adjLists, w, v);
            low[v] = MIN2(low[v], low[w]);
        }
        else if (w != u)        // back edge
            low[v] = MIN2(low[w], dfn[w]);
    }
}

void bicon(GraphNode *adjLists[], int v, int u)
{
    GraphNode *node;
    int w;
    int v1, v2;
    low[v] = dfn[v] = next_dfn++;
    for (node = adjLists[v]; node; node = node->link) {
        w = node->vertex;
        if (dfn[w] == -1) {
            pushBack(v), pushBack(w);   // push (v, w)
            bicon(adjLists, w, v);
            if (dfn[v] <= low[w]) {
                printf("new binconnected component : ");
                do {
                    v2 = back(), popBack();
                    v1 = back(), popBack();
                    printf("<%d, %d> ", v1, v2);
                } while (v1 != v || v2 != w);   // pop until (v, w)
                printf("\n");
            }
            low[v] = MIN2(low[v], low[w]);
        }
        else if (w != u) {
            pushBack(v), pushBack(w);   // push (v, w)
            low[v] = MIN2(low[v], dfn[w]);
        }
    }
}

/* main */

#define MAX_VERTICES 10
int main()
{
    int i;

    GraphNode *adjLists[MAX_VERTICES] = {
        newNode((1), 1),
        newNode((3), 0, 2, 3),
        newNode((2), 1, 4),
        newNode((3), 4, 1, 5),
        newNode((2), 2, 3),
        newNode((3), 3, 6, 7),
        newNode((2), 5, 7),
        newNode((4), 5, 6, 9, 8),
        newNode((1), 7),
        newNode((1), 7)
    };

    printf("dfs : ");
    visited_init(MAX_VERTICES);
    dfs(adjLists, 3);
    printf("\n");

    printf("bfs : ");
    init(), visited_init(MAX_VERTICES);
    bfs(adjLists, 3);
    printf("\n");

    visited_init(MAX_VERTICES);
    connected(adjLists, MAX_VERTICES);

    init(), dfnlow_init(MAX_VERTICES);
    bicon(adjLists, 3, -1);
    printf("dfn : ");
    for (i = 0; i < MAX_VERTICES; i++)
        printf("%3d", dfn[i]);
    printf("\n");
    printf("low : ");
    for (i = 0; i < MAX_VERTICES; i++)
        printf("%3d", low[i]);
    printf("\n");

    return 0;
}