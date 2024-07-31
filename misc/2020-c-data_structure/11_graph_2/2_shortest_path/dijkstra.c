/* Dijkstra algorithm
 * 20200203
 * shortest path는 directed graph 대상, 강의노트에서는 인접 행렬을 대상으로 했으나 여기서는 인접 리스트를 대상으로 하였음
 * dist[], pi[], found[](visited)
 * infinity는 최댓값 혹은 bool inf[]로 판별
 * found로 노드 확정하는 것은 더 이상 최소 거리가 나오지 않는다는 전제를 요구 (negative cost 배제)
 * O(|V|/|E| + |V|)를 |V|-1 반복하므로 O(|V|^2)
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

void dijkstra(GraphNode *adjLists[], int size, int v)
{
    int i, j, w;
    GraphNode *node;
    int dist[size], pi[size];
    bool found[size];

    for (i = 0; i < size; i++)
        dist[i] = INF, pi[i] = -1, found[i] = false;

    printf("Dijkstra Shortest Path : \n");
    dist[v] = 0;
    for (i = 0; i < size - 1; i++) {
        found[v] = true;
        for (node = adjLists[v]; node; node = node->link) {
            w = node->vertex;
            if (found[w])
                continue;
            if (dist[w] == INF) {
                if (dist[v] != INF) {
                    dist[w] = dist[v] + node->weight;
                    pi[w] = v;
                }
            }
            else { 
                if (dist[v] != INF && dist[w] > dist[v] + node->weight) {
                    dist[w] = dist[v] + node->weight;   // edge relaxation
                    pi[w] = v;
                }
            }
        }
        v = -1;
        for (j = 0; j < size; j++) {
            if (found[j] || dist[j] == INF)
                continue;
            if (v == -1 || dist[v] > dist[j])
                v = j;
        }
        if (v == -1)
            break;
        printf("%d) ", v);
        printPath(pi, v);
        printf(" : %d\n", dist[v]);
    }
}

/* main */

#define MAX_VERTICES 6
int main()
{
    GraphNode *adjLists[] = {
        newNode((3), 1, 50, 2, 10, 4, 45),
        newNode((2), 2, 15, 4, 10),
        newNode((2), 0, 20, 3, 15),
        newNode((2), 1, 20, 4, 35),
        newNode((1), 3, 30),
        newNode((1), 5, 3)
    };

    dijkstra(adjLists, MAX_VERTICES, 0);

    return 0;
}