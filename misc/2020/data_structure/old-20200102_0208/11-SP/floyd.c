#include <stdio.h>
#define INF 1000
#define MAX_VERTICES 100

/* it assumes that there are no cycle with zero or negative cost. */
void floydwarshall(int cost[][MAX_VERTICES], int dist[][MAX_VERTICES], int n)
{
    // O(|V||E|) = O(|V|^3)
    int i, j, k;
    for (i = 0; i < n; i++)     // A^(-1)
        for (j = 0; j < n; j++)
            dist[i][j] = cost[i][j];
    for (k = 0; k < n; k++) {   // A^0 to A^(n-1)
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int main()
{
    int adjmat[][MAX_VERTICES] = {
        {0, 4, 11},
        {6, 0, 2},
        {3, INF, 0}
    };
    int dist[MAX_VERTICES][MAX_VERTICES] = {0};

    floydwarshall(adjmat, dist, 3);

    printf("Cost Matrix : {\n");
    for (int i = 0; i < 3; i++) {
        printf("\t");
        for (int j = 0; j < 3; j++)
            printf("%5d", dist[i][j]);
        printf("\n");
    }
    printf("}\n");
}