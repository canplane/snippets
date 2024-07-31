#ifndef __HDNODE_H__
#define __HDNODE_H__

typedef struct {
    int count;
    GraphNode *link;
} HDNode;

void hdNodes_init(HDNode hdNodes[], GraphNode *adjLists[], int size)
{
    int i;
    GraphNode *node;

    for (i = 0; i < size; i++)
        hdNodes[i].count = 0, hdNodes[i].link = adjLists[i];
    for (i = 0; i < size; i++)
        for (node = adjLists[i]; node; node = node->link)
            hdNodes[node->vertex].count++;
}

#endif