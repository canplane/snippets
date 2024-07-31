//#include "avl.c"
#include "redblack.c"

#define DATASZ 8
int main()
{
    int i;
    Element e;
    Tree *root;
    int data[DATASZ] = {10, 85, 15, 70, 20, 60, 30, 50};

    init(&root);

    // insertion
    for (i = 0; i < DATASZ; i++) {
        printf("-------- insert %d --------\n", data[i]);
        e.key = data[i];
        insert(&root, e);
        printTree(root);
        printf("\n");
    }

    // deletion
    for (i = 0; !empty(root); i++) {
        printf("-------- delete %d --------\n", root->item.key);
        delete(&root, root->item.key);
        printTree(root);
        printf("\n");
    }
    printf("\n");

    return 0;
}