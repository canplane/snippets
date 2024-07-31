/* min heap */
#define MAXSZ 100

Edge *heap[MAXSZ];
int n;

void push(Edge *e)
{
    int i;
    if (n == MAXSZ - 1)
        return;
    for (i = ++n; i > 1 && e->weight < heap[i/2]->weight; i /= 2)
        heap[i] = heap[i/2];
    heap[i] = e;
}
Edge *pop()
{
    Edge *e;
    int i;
    if (n == 0)
        return NULL;
    e = heap[n--];
    heap[0] = heap[1];
    for (i = 2; i <= n; i *= 2) {
        if (i + 1 <= n && heap[i]->weight > heap[i + 1]->weight)
            i++;
        if (e->weight > heap[i]->weight)
            heap[i/2] = heap[i];
        else
            break;
    }
    heap[i/2] = e;
    return heap[0];
}