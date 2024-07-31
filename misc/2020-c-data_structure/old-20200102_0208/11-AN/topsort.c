/* topological sort (activity on vertex, aov)
 * e.g. curriculum, prerequisites
 * 20200127_2150
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* adjacency list */

typedef struct node {
    int vertex;
    struct node *link;
} Node;

static Node *_newNode(int argc, va_list ap)
{
    Node *node = NULL;
    if (argc) {
        node = malloc(sizeof(Node));
        node->vertex = va_arg(ap, int);
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

/* topological sort */

void topSort(HDNode hdNodes[], int n)
{
    int top, i, j, k;
    Node *node;
    top = -1;
    for (i = 0; i < n; i++) {
        if (!hdNodes[i].count) {
            hdNodes[i].count = top;
            top = i;
        }
    }
    for (i = 0; i < n; i++) {
        if (top == -1) {
            fprintf(stderr, "networt has a cycle\n");
            return;
        }
        printf("%d, ", top);
        j = top;
        top = hdNodes[top].count;
        for (node = hdNodes[j].link; node; node = node->link) {
            k = node->vertex;
            if (!--hdNodes[k].count) {
                hdNodes[k].count = top;
                top = k;
            }
        }
    }
}

/* main */

#define MAX_VERTICES 6
int main()
{
    Node *adjList[MAX_VERTICES] = {
        newNode((3), 1, 2, 3),
        newNode((1), 4),
        newNode((2), 4, 5),
        newNode((2), 4, 5),
        newNode((0)),
        newNode((0))
    };
    HDNode hdNodes[MAX_VERTICES];

    hdNodes_init(hdNodes, adjList, MAX_VERTICES);
    topSort(hdNodes, MAX_VERTICES);

    return 0;    
}