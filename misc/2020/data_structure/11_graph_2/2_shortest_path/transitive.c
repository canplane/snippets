/* transitive closure
 * 20200205
 * Floyd-Warshall algorithm과 유사하나 infinity를 0, 나머지는 1로 둠
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void transitive(int size, bool dist[][size], bool cost[][size], bool reflexive)
{
    int k, row, col;

    for (row = 0; row < size; row++)
        for (col = 0; col < size; col++)
            dist[row][col] = (row == col && reflexive) ? 1 : cost[row][col];

    for (k = 0; k < size; k++)
        for (row = 0; row < size; row++)
            for (col = 0; col < size; col++)
                dist[row][col] = dist[row][col] || (dist[row][k] && dist[k][col]);
}

/* main */

#define MAX_VERTICES 5
int main()
{
    int row, col;
    bool adjMat[][MAX_VERTICES] = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0}
    };
    bool dist[MAX_VERTICES][MAX_VERTICES];

    printf("transitive closure = {\n");
    transitive(MAX_VERTICES, dist, adjMat, false);
    for (row = 0; row < MAX_VERTICES; row++) {
        for (col = 0; col < MAX_VERTICES; col++)
            printf("%4d", dist[row][col]);
        printf("\n");
    }
    printf("}\n");

    printf("reflexive transitive closure = {\n");
    transitive(MAX_VERTICES, dist, adjMat, true);
    for (row = 0; row < MAX_VERTICES; row++) {
        for (col = 0; col < MAX_VERTICES; col++)
            printf("%4d", dist[row][col]);
        printf("\n");
    }
    printf("}\n");

    return 0;
}