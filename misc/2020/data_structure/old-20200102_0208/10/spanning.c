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

void bfs(int v)
{
    int adj;
    Node *node;
    visited[v] = true;
    printf("%5d", v);
    enqueue(v);
    while ((v = dequeue()) != -1) {
        for (node = graph[v]; node; node = node->link) {
            if (!visited[adj = node->vertex]) {
                visited[adj] = true;
                printf("%5d", adj);
                enqueue(adj);
            }
        }
    }
}

/* connected components */
void connected()
{
    int i;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            printf("\n");
        }
    }
}

/* spanning tree */
Node *tree[MAXSZ];

void dfst(int v, int parent)
{
    int adj;
    Node *node, *child;
    visited[v] = true;
    printf("%5d", v);
    for (node = graph[v]; node; node = node->link) {
        if (!visited[adj = node->vertex]) {
            child = malloc(sizeof(Node));
            child->vertex = adj;
            child->link = tree[v];
            tree[v] = child;
            dfs(adj, v);
        }
    }
}

/* biconnected components */
#define MIN2(x, y) ((x) < (y) ? (x) : (y))
unsigned int dfn[MAXSZ] = {-1, }, low[MAXSZ] = {-1, }, next_dfn;

void dfnlow(int v, int parent)
{
    int adj;
    Node *node;
    low[v] = dfn[v] = next_dfn++;                       // dfn
    for (node = graph[v]; node; node = node->link) {
        if (dfn[adj = node->vertex] == -1) {            // child
            dfnlow(adj, v);
            low[v] = MIN2(low[v], low[adj]);
        }
        else if (adj != parent && dfn[adj] < dfn[v])    // back edge
            low[v] = MIN2(low[v], dfn[adj]);
    }
}

int stack[MAXSZ][2], top = -1;
void push(int v1, int v2)
{
    ++top;
    stack[top][0] = v1;
    stack[top][1] = v2; 
}
int *pop()
{
    if (top == -1)
        return NULL;
    return stack[top--];
}
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
