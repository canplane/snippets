/* 이거 insert는 되는데 delete가 이상한 듯. 그냥 삽입 or 삭제 후 rebalance하자 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct {
    int key;
} element;

/* AVL tree */

typedef struct tree {
    element item;
    short int bf;
    struct tree *lchild, *rchild;
} Tree;

void rotation(Tree **parent, int dir, bool *unbalanced)
{
    Tree *child, *grandchild;
    if (dir == 1) {
        child = (*parent)->lchild;
        if (child->bf == 1) {   // LL : single rotation
            (*parent)->lchild = child->rchild;
            child->rchild = *parent;
            (*parent)->bf = 0;
            *parent = child;
        }
        else {  // LR : double rotation
            grandchild = child->rchild;
            child->rchild = grandchild->lchild;
            grandchild->lchild = child;
            (*parent)->lchild = grandchild->rchild;
            grandchild->rchild = *parent;
            switch (grandchild->bf) {
            case 1:
                (*parent)->bf = -1, child->bf = 0;
                break;
            case -1:
                (*parent)->bf = 0, child->bf = 1;
                break;
            case 0:
                (*parent)->bf = child->bf = 0;
            }
            *parent = grandchild;
        }
    }
    else {
        child = (*parent)->rchild;
        if (child->bf == -1) {  // RR : single rotation
            (*parent)->rchild = child->lchild;
            child->lchild = *parent;
            (*parent)->bf = 0;
            *parent = child;
        }
        else {  // RL : double rotation
            grandchild = child->lchild;
            child->lchild = grandchild->rchild;
            grandchild->rchild = child;
            (*parent)->rchild = grandchild->lchild;
            grandchild->lchild = *parent;
            switch (grandchild->bf) {
            case -1:
                (*parent)->bf = 1, child->bf = 0;
                break;
            case 1:
                (*parent)->bf = 0, child->bf = -1;
                break;
            case 0:
                (*parent)->bf = child->bf = 0;
            *parent = grandchild;
            }
        }
    }
    (*parent)->bf = 0, *unbalanced = false;
}

void rebalance(Tree **tree, int dir, bool *unbalanced)
{
    // dir : 1(left), -1(right)
    if (*unbalanced) {
        if ((*tree)->bf == -dir) {
            (*tree)->bf = 0;
            *unbalanced = false;
        }
        else if ((*tree)->bf == 0)
            (*tree)->bf = dir;
        else
            rotation(tree, dir, unbalanced);
    }
}

bool insert(Tree **tree, element e, bool *unbalanced)
{
    bool ret;
    if (!*tree) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->bf = 0;
        (*tree)->lchild = (*tree)->rchild = NULL;
        return *unbalanced = true;
    }
    else if (e.key < (*tree)->item.key) {
        ret = insert(&(*tree)->lchild, e, unbalanced);
        rebalance(tree, 1, unbalanced);
        return ret;
    }
    else if (e.key > (*tree)->item.key) {
        ret = insert(&(*tree)->rchild, e, unbalanced);
        rebalance(tree, -1, unbalanced);
        return ret;
    }
    else {
        return *unbalanced = false;
    }
}

void replaceToDelete(Tree **tree, Tree **dst, bool *unbalanced)
{
    Tree *src;
    if ((*tree)->rchild) {
        replaceToDelete(&(*tree)->rchild, dst, unbalanced);
        rebalance(tree, 1, unbalanced);
    }
    else {
        src = *tree;
        if (*tree != (*dst)->lchild) {
            *tree = src->lchild;
            src->lchild = (*dst)->lchild;
        }
        src->rchild = (*dst)->rchild;
        src->bf = (*dst)->bf;
        *dst = src;
    }
}

bool delete(Tree **tree, int key, bool *unbalanced)
{
    bool ret;
    Tree *node;
    if (!*tree) {
        return *unbalanced = false;
    }
    else if (key < (*tree)->item.key) {
        ret = delete(&(*tree)->lchild, key, unbalanced);
        rebalance(tree, -1, unbalanced);
        return ret;
    }
    else if (key > (*tree)->item.key) {
        ret = delete(&(*tree)->rchild, key, unbalanced);
        rebalance(tree, 1, unbalanced);
        return ret;
    }
    else {
        node = *tree;
        if ((*tree)->lchild && (*tree)->rchild) {
            replaceToDelete(&(*tree)->lchild, tree, unbalanced);
            rebalance(tree, -1, unbalanced);
        }
        else
            *tree = (*tree)->lchild ? (*tree)->lchild : (*tree)->rchild;
        free(node);
        return *unbalanced = true;
    }
}

/* main */

void printTree(Tree *tree, Tree *parent, int dir)
{
    if (tree) {
        printf(".%2d(%2d,%2d,%2d) ", tree->item.key, parent->item.key, tree->bf, dir);
        printTree(tree->lchild, tree, 1);
        printTree(tree->rchild, tree, -1);
    }
}

int main()
{
    int i;
    bool unbalanced;
    element e;
    Tree *root = NULL;
    for (i = 1; i <= 10; i++) {
        e.key = i;
        insert(&root, e, &unbalanced);
        printf("----- %d -----\n", i);
        printTree(root, root, 0);
        printf("\n\n");
    }
    printf("[end]\n\n");
    for (i = 1; i <= 10; i++) {
        delete(&root, root->item.key, &unbalanced);
        printf("----- %d -----\n", i);
        printTree(root, root, 0);
        printf("\n\n");
    }
    return 0;
}