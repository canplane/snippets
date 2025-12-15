/* critical activity (activity on edge, aoe)
 * 간선은 각 태스크가 완료되기까지 시간, 노드는 각 태스크가 완료된 시점
 * 20200128_0244
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct node {
    int vertex;
    int duration;
    struct node *link;
} Node;

static Node *_newNode(int argc, va_list ap)
{
    Node *node = NULL;
    if (argc) {
        node = malloc(sizeof(Node));
        node->vertex = va_arg(ap, int);
        node->duration = va_arg(ap, int);
        node->link = _newNode(--argc, ap);
    }
    return node;
}
Node *newNode(int argc, ...)
{
    Node *node;
    va_list ap;
    va_start(ap, argc);
    node = _newNode(argc, ap);
    va_end(ap);
    return node;
}

void inverse(Node *dst[], Node *src[], int n)
{
    int i, j;
    Node *node, *tmp;

    for (i = 0; i < n; i++)
        dst[i] = NULL;
    for (i = 0; i < n; i++) {
        for (node = src[i]; node; node = node->link) {
            j = node->vertex;
            tmp = malloc(sizeof(Node));
            tmp->vertex = i;
            tmp->duration = node->duration;
            tmp->link = dst[j];
            dst[j] = tmp;
        }
    }
}

/* activity network */

typedef struct {
    int count;
    Node *link;
} HDNode;

void hdNodes_init(HDNode hdNodes[], Node *adjList[], int n)
{
    int i;
    Node *node;
    for (i = 0; i < n; i++) {
        hdNodes[i].count = 0;
        hdNodes[i].link = adjList[i];
        for (node = adjList[i]; node; node = node->link)
            hdNodes[node->vertex].count++;
    }
}

/* critical activity */

void earliest(HDNode hdNodes[], int early[], int back[], int n)
{
    int top, i, j, k;
    Node *node;
    int len;

    top = -1;
    for (i = 0; i < n; i++) {
        early[i] = -1;
        back[i] = -1;
        if (!hdNodes[i].count) {
            hdNodes[i].count = top;
            top = i;
            early[i] = 0;
        }
    }
    for (i = 0; i < n; i++) {
        if (top == -1) {
            fprintf(stderr, "network has a cycle\n");
            return;
        }
        j = top;
        top = hdNodes[j].count;
        for (node = hdNodes[j].link; node; node = node->link) {
            k = node->vertex;
            if (!--hdNodes[k].count) {
                hdNodes[k].count = top;
                top = k;
            }
            if (early[k] < early[j] + node->duration) {
                early[k] = early[j] + node->duration;
                back[k] = j;
            }
        }
    }
    len = early[j];

    for (i = 0; i < n; i++)
        printf("%d : earliest = %d\n", i, early[i]);
    printf("critical path (<-) : ");
    do
        printf("%d ", j);
    while ((j = back[j]) != -1);
    printf("(length : %d)\n", len);
}

void latest(HDNode inv_hdNodes[], int late[], int back[], int n)
{
    int top, i, j, k;
    Node *node;
    int len;

    top = -1;
    for (i = 0; i < n; i++) {
        late[i] = 1;    // 반대니까 1
        back[i] = -1;
        if (!inv_hdNodes[i].count) {
            inv_hdNodes[i].count = top;
            top = i;
            late[i] = 0;
        }
    }
    for (i = 0; i < n; i++) {
        if (top == -1) {
            fprintf(stderr, "network has a cycle\n");
            return;
        }
        j = top;
        top = inv_hdNodes[j].count;
        for (node = inv_hdNodes[j].link; node; node = node->link) {
            k = node->vertex;
            if (!--inv_hdNodes[k].count) {
                inv_hdNodes[k].count = top;
                top = k;
            }
            if (late[k] > late[j] - node->duration) {
                late[k] = late[j] - node->duration;
                back[k] = j;
            }
        }
    }
    //
    len = -late[j];
    for (i = 0; i < n; i++)
        late[i] += len;
    //

    for (i = 0; i < n; i++)
        printf("%d : latest = %d\n", i, late[i]);
    printf("critical path (->) : ");
    do
        printf("%d ", j);
    while ((j = back[j]) != -1);
    printf("(length : %d)\n", len);
}

/* main */

#define MAX_VERTICES 9
int main()
{
    Node *adjList[MAX_VERTICES] = {
        newNode((3), 1, 6, 2, 4, 3, 5),
        newNode((1), 4, 1),
        newNode((1), 4, 1),
        newNode((1), 5, 2),
        newNode((2), 6, 8, 7, 7),
        newNode((1), 7, 4),
        newNode((1), 8, 2),
        newNode((1), 8, 4),
        newNode((0))
    };
    Node *inv_adjList[MAX_VERTICES];
    HDNode hdNodes[MAX_VERTICES];
    int times[MAX_VERTICES], back[MAX_VERTICES];

    printf("-------- earliest time (using adj list) --------\n");
    hdNodes_init(hdNodes, adjList, MAX_VERTICES);
    earliest(hdNodes, times, back, MAX_VERTICES);
    printf("\n");

    printf("-------- latest time (using inverse adj list) --------\n");
    inverse(inv_adjList, adjList, MAX_VERTICES);
    hdNodes_init(hdNodes, inv_adjList, MAX_VERTICES);
    latest(hdNodes, times, back, MAX_VERTICES);

    return 0;
}