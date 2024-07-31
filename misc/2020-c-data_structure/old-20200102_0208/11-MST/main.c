#include "mst.c"
#define MAX_VERTICES 7

/* main */
int main(int argc, const char *argv[])
{
    Node *adjlist[MAX_VERTICES];
    adjlist[0] = set_node((2), 1, 28, 5, 10);
    adjlist[1] = set_node((3), 0, 28, 2, 16, 6, 14);
    adjlist[2] = set_node((2), 1, 16, 3, 12);
    adjlist[3] = set_node((3), 2, 12, 4, 22, 6, 18);
    adjlist[4] = set_node((3), 3, 22, 5, 25, 6, 24);
    adjlist[5] = set_node((2), 0, 10, 4, 25);
    adjlist[6] = set_node((3), 1, 14, 3, 18, 4, 24);
    prim(adjlist, MAX_VERTICES);
}