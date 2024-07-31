/* disjoint set
 * 20200128_2030
 * 데이터 수 많으면 find -> collapsingFind, simpleUnion -> weightUnion
 * e.g. equivalent class(symbol : three =), cycle
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSZ 100

int parent[MAXSZ];

void init(int sz)
{
    while (--sz + 1)
        parent[sz] = -1;
}

/*
void find(int x)
{
    for (; parent[x] >= 0; x = parent[x]);
    return x;
}
*/

// uFind 대신 collapsingFind 쓰자
void collapsingFind(int x)
{
    int root, tmp;
    for (root = x; parent[root] >= 0; root = parent[root]);
    for (; x != root; x = tmp) {
        tmp = parent[x];
        parent[x] = root;
    }
    return root;
}

/* simple union */

void simpleUnion(int x, int y)
{
    if (x != y) {
        x = find(x);
        //y = find(y); // 굳이 쓸 필요 없음
        parent[x] = y;
    }
}

/* weighted union */

void weightedUnion(int x, int y)
{
    int tmp;
    if (x != y) {
        x = find(x);
        y = find(y);
        tmp = parent[x] + parent[y];
        if (parent[x] < parent[y]) {
            parent[y] = x;
            parent[x] = tmp;
        }
        else {
            parent[x] = y;
            parent[y] = tmp;
        }
    }
}
