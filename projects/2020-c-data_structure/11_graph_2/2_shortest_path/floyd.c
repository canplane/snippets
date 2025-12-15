/* Floyd-Warshall algorithm
 * 20200204
 * zero or negative cycle 없다고 가정
 * dist[][], cost[][] (인접 행렬을 입출력으로 이용)
 * A^k (k = -1, 0, ..., n-1) (path between i and j의 intermediate vertices의 index <= k)
 * 따라서 A^(-1)는 인접 행렬과 같음
 * O(|V||E|) = O(|V|^3)
 */

#include <stdio.h>

#define MIN2(x, y) ((x) < (y) ? (x) : (y))

#define INF 0x7FFFFFFF

void floyd(int size, int dist[][size], int cost[][size])
{
    int k, row, col;

    // k = -1
    for (row = 0; row < size; row++)
        for (col = 0; col < size; col++)
            dist[row][col] = cost[row][col];
    // k = 0, 1, ..., (size - 1)
    for (k = 0; k < size; k++) {
        for (row = 0; row < size; row++) {
            for (col = 0; col < size; col++) {
                dist[row][col] = MIN2(dist[row][k] + dist[k][col], dist[row][col]);
            }
        }
    }
}

/* main */

#define MAX_VERTICES 3
int main()
{
    int row, col;
    int adjMat[][MAX_VERTICES] = {
        {0, 4, 11},
        {6, 0, 2},
        {3, INF, 0}
    };
    int dist[MAX_VERTICES][MAX_VERTICES];

    floyd(MAX_VERTICES, dist, adjMat);
    printf("dist = {\n");
    for (row = 0; row < MAX_VERTICES; row++) {
        for (col = 0; col < MAX_VERTICES; col++) {
            if (dist[row][col] == INF)
                printf("INF ");
            else
                printf("%4d", dist[row][col]);
        }
        printf("\n");
    }
    printf("}\n");

    return 0;
}
