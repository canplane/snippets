#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct {
    int key;
} Element;

typedef struct tree {
    Element item;
    struct tree *lchild, *rchild;
} Tree;

void init(Tree **tree)
{
    *tree = NULL;
}

bool empty(Tree *tree)
{
    return !tree;
}

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

static void _transplant(Tree **tree, Tree **dst)
{
    Tree *src;
    if ((*tree)->rchild)
        _transplant(&(*tree)->rchild, dst);
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
    Tree *target;
    if (!*tree)
        return false;
    else if (key < (*tree)->item.key)
        return delete(&(*tree)->lchild, key);
    else if (key > (*tree)->item.key)
        return delete(&(*tree)->rchild, key);
    else {
        target = *tree;
        if (target->lchild && target->rchild)
            _transplant(tree, tree);
        else
            *tree = target->lchild ? target->lchild : target->rchild;
        free(target);
        return true;
    }
}

enum {LEFT = -1, RIGHT = 1};
static void _printTree(Tree *tree, Tree *parent, int dir)
{
    if (tree) {
        if (dir)
            printf("%d : %s child of %d\n", tree->item.key, dir == LEFT ? "left" : "right", parent->item.key);
        else
            printf("%d : root\n", tree->item.key);
        _printTree(tree->lchild, tree, LEFT);
        _printTree(tree->rchild, tree, RIGHT);
    }
}

void printTree(Tree *root)
{
    if (root)
        _printTree(root, root, 0);
    else
        printf("EMPTY\n");
}
