/* 20200124 */

/* 기존의 BST 삽입, 삭제 절차 이후 rebalance() 추가 */
/* rebalance()에서 null 주의 */

#include <stdio.h>
#include <stdlib.h>

#define MAX2(x, y) ((x) > (y) ? (x) : (y))

typedef enum {false, true} bool;

typedef struct {
    int key;
} Element;

/* Data Types */

typedef struct tree {
    Element item;
    int h;
    short bf;
    struct tree *lchild, *rchild;
} Tree;

/* Internal Balancing Functions */

static void _update_bf(Tree *tree)
{
    if (tree->lchild && tree->rchild) {
        tree->h = MAX2(tree->lchild->h, tree->rchild->h) + 1;
        tree->bf = tree->lchild->h - tree->rchild->h;
    }
    else if (tree->lchild) {
        tree->h = tree->lchild->h + 1;
        tree->bf = tree->h;
    }
    else if (tree->rchild) {
        tree->h = tree->rchild->h + 1;
        tree->bf = -tree->h;
    }
    else
        tree->bf = tree->h = 0;
}

static void _rebalance(Tree **tree)
{
    Tree *parent, *child, *grandchild;
    parent = *tree;
    _update_bf(parent);
    if (parent->bf > 1) {
        child = parent->lchild;
        if (child->bf > -1) {   // LL
            parent->lchild = child->rchild;
            child->rchild = parent;
            _update_bf(parent);
            _update_bf(child);
            *tree = child;
        }
        else {  // LR
            grandchild = child->rchild;
            child->rchild = grandchild->lchild;
            parent->lchild = grandchild->rchild;
            grandchild->lchild = child;
            grandchild->rchild = parent;
            _update_bf(parent);
            _update_bf(child);
            _update_bf(grandchild);
            *tree = grandchild;
        }
    }
    else if (parent->bf < -1) {
        child = parent->rchild;
        if (child->bf < 1) {   // RR
            parent->rchild = child->lchild;
            child->lchild = parent;
            _update_bf(parent);
            _update_bf(child);
            *tree = child;
        }
        else {  // RL
            grandchild = child->lchild;
            child->lchild = grandchild->rchild;
            parent->rchild = grandchild->lchild;
            grandchild->rchild = child;
            grandchild->lchild = parent;
            _update_bf(parent);
            _update_bf(child);
            _update_bf(grandchild);
            *tree = grandchild;
        }
    }
}

/* Internal Accessing Functions */

static void _transplant(Tree **tree, Tree **dst)
{
    Tree *src;
    if ((*tree)->rchild) {
        _transplant(&(*tree)->rchild, dst);
        _rebalance(tree);
    }
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

/* External Functions */

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
    if (key < tree->item.key)
        return search(tree->lchild, key);
    else if (key > tree->item.key)
        return search(tree->rchild, key);
    else
        return &tree->item;
}

bool insert(Tree **tree, Element e)
{
    bool ret;
    if (!*tree) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NULL;
        ret = true;
    }
    else if (e.key < (*tree)->item.key)
        ret = insert(&(*tree)->lchild, e);
    else if (e.key > (*tree)->item.key)
        ret = insert(&(*tree)->rchild, e);
    else
        ret = false;
    if (ret)
        _rebalance(tree);
    return ret;
}

bool delete(Tree **tree, int key)
{
    bool ret;
    Tree *target;
    if (!*tree)
        ret = false;
    else if (key < (*tree)->item.key)
        ret = delete(&(*tree)->lchild, key);
    else if (key > (*tree)->item.key)
        ret = delete(&(*tree)->rchild, key);
    else {
        target = *tree;
        if (target->lchild && target->rchild) {
            _transplant(&target->lchild, tree);
            _rebalance(tree);
        }
        else
            *tree = target->lchild ? target->lchild : target->rchild;
        free(target);
        return true;
    }
    if (ret)
        _rebalance(tree);
    return ret;
}

void printTree(Tree *root)
{
    if (root != NULL)
        _printTree(root, root, 0);
    else
        printf("EMPTY\n");
}
