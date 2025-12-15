#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAXSZ 100

typedef enum {false, true} bool;

/* adjacency list */
typedef struct node {
    int vertex;
    struct node *link;
} Node;
Node *graph[MAXSZ];

bool visited[MAXSZ];

/* dfs */
void dfs(int v)
{
    Node *node;
    visited[v] = true;
    printf("%5d", v);
    for (node = graph[v]; node; node = node->link) {
        if (!visited[node->vertex])
            dfs(node->vertex);
    }
}

/* bfs */
int queue[MAXSZ];
int front, rear;
void enqueue(int e)
{
    rear = (rear + 1) % MAXSZ;
    if (front == rear)
        return;
    queue[rear] = e;
}
int dequeue()
{
    if (front == rear)
        return -1;
    front = (front + 1) % MAXSZ;
    return queue[front];
}

void bfs(int v)
{
    Node *node;
    visited[v] = true; //
    printf("%5d", v); //
    enqueue(v);
    while ((v = dequeue()) != -1) {
        for (node = graph[v]; node; node = node->link) {
            if (!visited[v = node->vertex]) {
                visited[v] = true; //
                printf("%5d", v); //
                enqueue(v);
            }
        }
    }
}

/* biconnected components */
#define MIN2(x, y) ((x) < (y) ? (x) : (y))

int stack[MAXSZ][2], top = -1;
void push(int v1, int v2)
{
    ++top;
    stack[top][0] = v1;
    stack[top][1] = v2;
}
int *pop()
{
    return stack[top--];
}

int dfn[MAXSZ], low[MAXSZ], next_dfn;

void bicon(int v, int parent)
{
    int adj, *edge;
    Node *node;
    low[v] = dfn[v] = next_dfn++;
    for (node = graph[v]; node; node = node->link) {
        adj = node->vertex;
        if (dfn[adj] < 0) {
            push(adj, v);
            bicon(adj, v);
            low[v] = MIN2(low[v], low[adj]);
            if (dfn[v] <= low[adj]) {
                printf("New Biconnected Component :");
                do {
                    edge = pop();
                    printf(" <%d, %d>", edge[0], edge[1]);
                } while (edge[0] != adj || edge[1] != v);
                printf("\n");
            }
        }
        else if (adj != parent && dfn[adj] < dfn[v]) {
            push(adj, v);
            low[v] = MIN2(low[v], dfn[adj]);
        }
    }
}

/* main */

Node *newNode(int vertex, Node *link)
{
    Node *node = malloc(sizeof(Node));
    node->vertex = vertex;
    node->link = link;
    return node;
}
/*
Node *v_newNode(int argc, ...)
{
    Node *node = NULL, *temp = NULL;
    va_list ap;
    va_start(ap, argc);
    if (argc) {
        node = malloc(sizeof(Node));
        node->vertex = va_arg(ap, int);
        node->link = temp;
        temp = node;
    }
    va_end(ap);
    printf("\n");
    return node;
}
*/
Node *_v_newNode(int argc, va_list ap)
{
    Node *node = NULL;
    if (argc) {
        node = malloc(sizeof(Node));
        node->vertex = va_arg(ap, int);
        node->link = _v_newNode(--argc, ap);
    }
    return node;
}

Node *v_newNode(int argc, ...)
{
    Node *node;
    va_list ap;
    va_start(ap, argc);
    node = _v_newNode(argc, ap);
    va_end(ap);
    return node;
}

int main()
{
    int i;
    /*
    graph[0] = newNode(1, newNode(2, NULL));
    graph[1] = newNode(0, newNode(3, newNode(4, NULL)));
    graph[2] = newNode(0, newNode(5, newNode(6, NULL)));
    graph[3] = newNode(1, newNode(7, NULL));
    graph[4] = newNode(1, newNode(7, NULL));
    graph[5] = newNode(2, newNode(7, NULL));
    graph[6] = newNode(2, newNode(7, NULL));
    graph[7] = newNode(3, newNode(4, newNode(5, newNode(6, NULL))));
     */
    /*
    graph[0] = newNode(1, NULL);
    graph[1] = newNode(0, newNode(2, newNode(3, NULL)));
    graph[2] = newNode(1, newNode(4, NULL));
    graph[3] = newNode(4, newNode(1, newNode(5, NULL)));
    graph[4] = newNode(2, newNode(3, NULL));
    graph[5] = newNode(3, newNode(6, newNode(7, NULL)));
    graph[6] = newNode(5, newNode(7, NULL));
    graph[7] = newNode(5, newNode(6, newNode(9, newNode(8, NULL))));
    graph[8] = newNode(7, NULL);
    graph[9] = newNode(7, NULL);
     */
    graph[0] = v_newNode((1), 2);
    graph[1] = v_newNode((2), 2, 3);
    graph[2] = v_newNode((3), 0, 1, 4);
    graph[3] = v_newNode((4), 1, 4, 5, 9);
    graph[4] = v_newNode((2), 2, 3);
    graph[5] = v_newNode((4), 3, 6, 7, 9);
    graph[6] = v_newNode((2), 5, 8);
    graph[7] = v_newNode((2), 5, 9);
    graph[8] = v_newNode((1), 6);
    graph[9] = v_newNode((3), 3, 5, 7);
    
    printf("dfs : ");
    dfs(0);
    printf("\n");

    memset(visited, 0, MAXSZ);
    printf("bfs : ");
    bfs(0);
    printf("\n");

    memset(dfn, -1, sizeof(dfn));
    /*
    dfnlow(3, -1);
    printf("dfn : ");
    for (i = 0; i <= 9; i++)
        printf("%d ", dfn[i]);
    printf("\n");
    printf("low : ");
    for (i = 0; i <= 9; i++)
        printf("%d ", low[i]);
    printf("\n");
     */
    bicon(0, -1);
}
