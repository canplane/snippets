//#include "bst.c"
#include "avl.c"
//#include "redblack.c"

#define KEYS_SZ 8
const int KEYS[KEYS_SZ] = {10, 85, 15, 70, 20, 60, 30, 50};

int main()
{
    int i;
    Element e;
    Tree *root = NULL;

    // init
    init(&root);

    // insertion
    printf("[INSERTION]\n\n");
    for (i = 0; i < KEYS_SZ; i++) {
        printf("-------- Inserted : %d --------\n", KEYS[i]);
        e.key = KEYS[i];
        insert(&root, e);
        printTree(root);
        printf("\n");
    }
    printf("\n");

    // deletion
    printf("[DELETION]\n\n");
    for (i = 0; !empty(root); i++) {
        printf("-------- Deleted : %d --------\n", root->item.key);
        delete(&root, root->item.key);
        printTree(root);
        printf("\n");
    }
    printf("\n");

    return 0;
}