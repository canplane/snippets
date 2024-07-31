#include "b.c"

#define DATASZ 20
int main()
{
    int i;
    Element e;
    BTree *root;
    char data[DATASZ] = {
        'A', 'C', 'G', 'N', 'H', 
        'E', 'K', 'Q', 'M', 'F', 
        'W', 'L', 'T', 'Z', 'D', 
        'P', 'R', 'X', 'Y', 'S'
    };

    init(&root);

    // insertion
    for (i = 0; i < DATASZ; i++) {
        printf("-------- insert %c --------\n", data[i]);
        e.key = data[i];
        insert(&root, e);
        printTree(root);
        printf("\n");
    }

    // deletion
    /*
    for (i = 0; !empty(root); i++) {
        printf("-------- delete %c --------\n", root->items[0].key);
        delete(&root, root->items[0].key);
        printTree(root);
        printf("\n");
    }
    printf("\n");
    */

    return 0;
}