/* crictical activity (activity on edge, aoe)
 * 20200204
 * 간선은 각 태스크가 완료되기까지 시간, 노드는 각 태스크가 완료된 시점
 * in-degree 노드가 모두 방문되어야 다음 노드 방문 가능하므로 ET는 max로 구함
 * LT는 out-degree 노드의 ET를 모두 충족해야 하므로 min으로 구함
 * early[], late[] 처음에 초기화할 때 그냥 0으로 두면 됨
 */

#include <stdio.h>
#include "../graph.h"
#include "hdnode.h"

void earliest(GraphNode *adjLists[], int size)
{
    HDNode hdNodes[size];
    int top, i, j, k;
    GraphNode *node;
    int early[size], len, link[size];

    hdNodes_init(hdNodes, adjLists, size);
    top = -1;
    for (i = 0; i < size; i++) {
        early[i] = 0, link[i] = -1; //
        if (!hdNodes[i].count)
            hdNodes[i].count = top, top = i;
    }
    for (i = 0; i < size; i++) {
        if (top == -1) {
            printf("network has a cycle\n");
            return;
        }
        top = hdNodes[j = top].count;
        for (node = hdNodes[j].link; node; node = node->link) {
            k = node->vertex;
            if (!--hdNodes[k].count)
                hdNodes[k].count = top, top = k;
            if (!early[k] || early[k] < early[j] + node->weight) {
                early[k] = early[j] + node->weight;
                link[k] = j;
            }
        }
    }
    len = early[k];

    printf("earliest time :");
    for (i = 0; i < size; i++)
        printf(" %d", early[i]);
    printf(", ");
    printf("critical path (<-) :");
    for (; k != -1; k = link[k])
        printf(" %d", k);
    printf(" (length %d)", len);
    printf("\n");
}

void latest(GraphNode *inv_adjLists[], int size)
{
    HDNode hdNodes[size];
    int top, i, j, k;
    GraphNode *node;
    int late[size], len, link[size];

    hdNodes_init(hdNodes, inv_adjLists, size);
    top = -1;
    for (i = 0; i < size; i++) {
        late[i] = 0, link[i] = -1;  //
        if (!hdNodes[i].count)
            hdNodes[i].count = top, top = i;
    }
    for (i = 0; i < size; i++) {
        if (top == -1) {
            printf("network has a cycle\n");
            return;
        }
        top = hdNodes[j = top].count;
        for (node = hdNodes[j].link; node; node = node->link) {
            k = node->vertex;
            if (!--hdNodes[k].count)
                hdNodes[k].count = top, top = k;
            if (!late[k] || late[k] > late[j] - node->weight) {
                late[k] = late[j] - node->weight;
                link[k] = j;
            }
        }
    }
    len = -late[k];
    for (i = 0; i < size; i++)
        late[i] += len;

    printf("latest time :");
    for (i = 0; i < size; i++)
        printf(" %d", late[i]);
    printf(", ");
    printf("critical path :");
    for (; k != -1; k = link[k])
        printf(" %d", k);
    printf(" (length %d)", len);
    printf("\n");
}

/* main */

void inverse(GraphNode *dst[], GraphNode *src[], int size)
{
    int i, k;
    GraphNode *node, *tmp;
    for (i = 0; i < size; i++)
        dst[i] = NULL;
    for (i = 0; i < size; i++) {
        for (node = src[i]; node; node = node->link) {
            k = node->vertex;
            tmp = malloc(sizeof(GraphNode));
            tmp->vertex = i, tmp->weight = node->weight, tmp->link = dst[k];
            dst[k] = tmp;
        }
    }
}

#define MAX_VERTICES 9
int main()
{
    GraphNode *adjLists[MAX_VERTICES] = {
        newNode((3), 1, 6, 2, 4, 3, 5),
        newNode((1), 4, 1),
        newNode((1), 4, 1),
        newNode((1), 5, 2),
        newNode((2), 6, 8, 7, 7),
        newNode((1), 7, 4),
        newNode((1), 8, 2),
        newNode((1), 8, 4),
        newNode((0))
    }, *inv_adjLists[MAX_VERTICES];
    HDNode hdNodes[MAX_VERTICES];

    inverse(inv_adjLists, adjLists, MAX_VERTICES);

    earliest(adjLists, MAX_VERTICES);
    latest(inv_adjLists, MAX_VERTICES);

    return 0;
}