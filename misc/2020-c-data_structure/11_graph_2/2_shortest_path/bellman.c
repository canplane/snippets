/* Bellman-Ford algorithm
 * 20200203
 * dist[], pi[]
 * negative cycle 판별 가능
 * O(|E|)를 |V|-1 반복하므로 O(|V|^3)
 */

#include <stdio.h>
#include <stdbool.h>
#include "../graph.h"

#define INF 0x7FFFFFFF

void printPath(int pi[], int v)
{
    if (pi[v] != -1) {
        printPath(pi, pi[v]);
        printf("->%d", v);
    }
    else
        printf("%d", v);
}

void bellman(GraphNode *adjLists[], int size, int v)
{
    int k, i, w;
    GraphNode *node;
    int dist[size], pi[size];

    for (i = 0; i < size; i++)
        dist[i] = INF, pi[i] = -1;

    dist[v] = 0;
    for (k = 0; k < size - 1; k++) {
        for (i = 0; i < size; i++) {
            for (node = adjLists[i]; node; node = node->link) {
                w = node->vertex;
                if (dist[w] == INF) {
                    if (dist[i] != INF) {
                        dist[w] = dist[i] + node->weight;
                        pi[w] = i;
                    }
                }
                else {
                    if (dist[i] != INF && dist[w] > dist[i] + node->weight) {
                        dist[w] = dist[i] + node->weight;
                        pi[w] = i;
                    }
                }
            }
        }
    }
    printf("Bellman-Ford Shortest Path : \n");
    for (i = 0; i < size; i++) {
        for (node = adjLists[i]; node; node = node->link) {
            w = node->vertex;
            if (dist[w] != INF && dist[i] != INF && dist[w] > dist[i] + node->weight) {
                printf("negative cycle detected\n");
                return;
            }
        }
    }
    for (i = 0; i < size; i++) {
        if (i != v && dist[i] != INF) {
            printf("%d) ", i);
            printPath(pi, i);
            printf(" : %d\n", dist[i]);
        }
    }
}

/* main */

#define MAX_VERTICES 5
int main()
{
    /* 
    GraphNode *adjLists[] = {   // negative cost
        newNode((2), 1, 7, 2, 5),
        newNode((1), 2, -5),
        newNode((0))
    };
     */
    /*
    GraphNode *adjLists[] = {   // negative cycle
        newNode((1), 1, 1),
        newNode((2), 0, -2, 2, 1),
        newNode((0))
    };
     */
    GraphNode *adjLists[] = {   // 강의노트 42쪽 (46쪽 잘못되었음 : dist[4] = -2가 참)
        newNode((2), 1, 6, 3, 7),
        newNode((3), 2, 5, 3, 8, 4, -4),
        newNode((1), 1, -2),
        newNode((2), 2, -3, 4, 9),
        newNode((2), 0, 2, 2, 7)
    };

    bellman(adjLists, MAX_VERTICES, 0);

    return 0;
}