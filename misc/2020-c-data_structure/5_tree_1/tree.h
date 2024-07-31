#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>

typedef struct {
    char key;
} Element;

typedef struct tree {
    Element item;
    struct tree *lchild, *rchild;
} Tree;

Tree *newTree(Element e, Tree *lchild, Tree *rchild)
{
    Tree *tree;
    tree = malloc(sizeof(Tree));
    tree->item = e;
    tree->lchild = lchild;
    tree->rchild = rchild;
    return tree;
}

#endif