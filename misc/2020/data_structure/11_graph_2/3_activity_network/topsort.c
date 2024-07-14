/* topological sort (activity on vertex, aov)
 * 20200204
 * e.g. curriculum, prerequisites
 */

#include <stdio.h>
#include "../graph.h"
#include "hdnode.h"

void topsort(GraphNode *adjLists[], int size)
{
    int top, i, j, k;
    GraphNode *node;
    HDNode hdNodes[size];

    hdNodes_init(hdNodes, adjLists, size);
    top = -1;
    for (i = 0; i < size; i++) {
        if (!hdNodes[i].count)
            hdNodes[i].count = top, top = i;
    }
    printf("topological sort : ");
    for (i = 0; i < size; i++) {
        if (top == -1) {
            printf("network has a cycle\n");
            return;
        }
        printf("%d ", top);
        top = hdNodes[j = top].count;
        for (node = hdNodes[j].link; node; node = node->link) {
            if (!--hdNodes[k = node->vertex].count)
                hdNodes[k].count = top, top = k;
        }
    }
    printf("\n");
}

/* main */

#define MAX_VERTICES 6
#define DUMMY -1
int main()
{
    GraphNode *adjLists[MAX_VERTICES] = {
        newNode((3), 1, DUMMY, 2, DUMMY, 3, DUMMY),
        newNode((1), 4, DUMMY),
        newNode((2), 4, DUMMY, 5, DUMMY),
        newNode((2), 4, DUMMY, 5, DUMMY),
        newNode((0)),
        newNode((0))
    };

    topsort(adjLists, MAX_VERTICES);

    return 0;
}