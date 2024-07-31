/* binary search tree
 * 20200201
 * 
 * terminology)
 * depth : the distance between a node and the root
 * -> level : depth + 1
 * height : # of edges on the longest path from a given node to a descendant leaf
 * -> height of tree : the height of the root node (the maximum level of any node in the tree)
 * (root : depth 0, leaf : height 0)
 * 
 * width : # of nodes in a level (# of siblings + 1)
 * breadth : # of leaves
 * size of tree : # of nodes in the tree
 * 
 * degree : for a given node, its # of children
 * -> degree of tree : the maximum degree of any node in the tree (k-ary tree : k)
 * 
 * internal node, branch node : any node of a tree that has child nodes
 * <-> external node : leaf node
 * 
 * neighbor : parent of child
 * distance : # of edges along the shortest path between two nodes
 * 
 * ordered tree : a rooted tree in which an ordering is specified for the children of each vertex
 * branch, link : edge
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
} Element;

typedef struct tree {
    Element item;
    struct tree *lchild, *rchild;
} Tree;

Element *search(Tree *tree, int key)
{
    if (!tree)
        return NULL;
    else if (key < tree->item.key)
        return search(tree->lchild, key);
    else if (key > tree->item.key)
        return search(tree->rchild, key);
    else
        return &tree->item;
}

bool insert(Tree **tree, Element e)
{
    if (!*tree) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NULL;
        return true;
    }
    else if (e.key < (*tree)->item.key)
        return insert(&(*tree)->lchild, e);
    else if (e.key > (*tree)->item.key)
        return insert(&(*tree)->rchild, e);
    else
        return false;
}

void transplant(Tree **tree, Tree **dst)
{
    Tree *src;
    if ((*tree)->rchild)
        transplant(&(*tree)->rchild, dst);
    else {
        src = *tree;
        if (src != (*dst)->lchild) {
            *tree = src->lchild;
            src->lchild = (*dst)->lchild;
        }
        src->rchild = (*dst)->rchild;        
        *dst = src;
    }
}
bool delete(Tree **tree, int key)
{
    Tree *node;
    if (!*tree)
        return false;
    else if (key < (*tree)->item.key)
        return delete(&(*tree)->lchild, key);
    else if (key > (*tree)->item.key)
        return delete(&(*tree)->rchild, key);
    else {
        node = *tree;
        if (node->lchild && node->rchild)
            transplant(&node->lchild, tree);
        else
            *tree = node->lchild ? node->lchild : node->rchild;
        free(node);
        return true;
    }
}

/* main */

enum {LEFT = -1, RIGHT = 1};
void printTree(Tree *tree, Tree *parent, int dir)
{
    if (tree) {
        if (dir)
            printf("%d (%s child of %d)\n", tree->item.key, dir == LEFT ? "left" : "right", parent->item.key);
        else
            printf("%d (root)\n", tree->item.key);
        printTree(tree->lchild, tree, LEFT);
        printTree(tree->rchild, tree, RIGHT);
    }
}

/* main */

#define ARRSZ 6
int main()
{
    int i;
    int arr[ARRSZ] = {15, 4, 27, 9, 11, 6};
    Element e;
    Tree *root = NULL;  //
    for (i = 0; i < ARRSZ; i++) {
        printf("insert %d --------\n", arr[i]);
        e.key = arr[i], insert(&root, e);
        printTree(root, root, 0);
    }
    for (i = 0; i < ARRSZ; i++) {
        printf("delete %d --------\n", arr[i]);
        delete(&root, arr[i]);
        printTree(root, root, 0);
    }
    return 0;
}