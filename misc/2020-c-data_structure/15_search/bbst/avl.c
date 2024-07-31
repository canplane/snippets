/* AVL tree
 * 20200208
 * 기존의 BST 삽입, 삭제 절차 이후 rebalance() 추가
 * updateBF(), rotate(), rebalance(), bool *unbalanced
 * unbalanced 먼저 확인하고 rebalance 함수로 넘어간다. (가지 치기 위해서)
 * bf로만 생각하려 하지 말고 height 필드 둬서 쉽게 가기. 업데이트한 게 기존 height와 같으면 *unbalanced = false로 바꿔서 가지 치기
 * 업데이트한 게 기존 height와 같으면 unbalanced = false로 바꿔서 가지 치기
 * 리스트든 트리든 처음에 NULL로 초기화하는 것 주의
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX2(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int key;
} Element;

typedef struct tree {
    Element item;
    int height;
    short bf;
    struct tree *lchild, *rchild;
} Tree;

/* balancing functions */

static void updateBF(Tree *tree)
{
    int lheight, rheight, tmp;
    lheight = tree->lchild ? tree->lchild->height : 0;
    rheight = tree->rchild ? tree->rchild->height : 0;
    tree->height = MAX2(lheight, rheight) + 1;
    tree->bf = lheight - rheight;
}

enum {LEFT = -1, RIGHT = 1};
enum {SINGLE, DOUBLE};
static void rotate(Tree **tree, int dir, int count)
{
    Tree *parent, *child;
    parent = *tree;
    if (dir == RIGHT) {
        if (count == DOUBLE)
            rotate(&(*tree)->lchild, LEFT, SINGLE);
        child = parent->lchild, parent->lchild = child->rchild, child->rchild = parent; 
    }
    else {
        if (count == DOUBLE)
            rotate(&(*tree)->rchild, RIGHT, SINGLE);
        child = parent->rchild, parent->rchild = child->lchild, child->lchild = parent;  
    }
    updateBF(parent);
    updateBF(child);
    *tree = child;
}

static void rebalance(Tree **tree, bool *unbalanced)
{
    int tmp;
    tmp = (*tree)->height;
    updateBF(*tree);
    if (tmp == (*tree)->height) {
        *unbalanced = false;
        return;
    }

    switch ((*tree)->bf) {
    case 2:
        switch ((*tree)->lchild->bf) {
        case 1:
        case 0:
            rotate(tree, RIGHT, SINGLE);
            break;
        case -1:
            rotate(tree, RIGHT, DOUBLE);
            break;
        }
        break;
    case -2:
        switch ((*tree)->rchild->bf) {
        case -1:
        case 0:
            rotate(tree, LEFT, SINGLE);
            break;
        case 1:
            rotate(tree, LEFT, DOUBLE);
            break;
        }
        break;
    }
}

/* external functions */

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

static bool _insert(Tree **tree, Element e, bool *unbalanced)
{
    bool ret;
    if (!*tree) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NULL;
        updateBF(*tree);
        return *unbalanced = true;
    }
    else if (e.key < (*tree)->item.key) {
        ret = _insert(&(*tree)->lchild, e, unbalanced);
        if (*unbalanced)
            rebalance(tree, unbalanced);
        return ret;
    }
    else if (e.key > (*tree)->item.key) {
        ret = _insert(&(*tree)->rchild, e, unbalanced);
        if (*unbalanced)
            rebalance(tree, unbalanced);
        return ret;
    }
    else
        return *unbalanced = false;
}
bool insert(Tree **tree, Element e)
{
    bool unbalanced;
    return _insert(tree, e, &unbalanced);
}

static void transplant(Tree **tree, Tree **dst, bool *unbalanced)
{
    Tree *src;
    if ((*tree)->rchild) {
        transplant(&(*tree)->rchild, dst, unbalanced);
        if (*unbalanced)
            rebalance(tree, unbalanced);
    }
    else {
        src = *tree;
        *unbalanced = true;
        if (src != (*dst)->lchild) {
            *tree = src->lchild;
            src->lchild = (*dst)->lchild;
        }
        src->rchild = (*dst)->rchild;
        *dst = src;
    }
}
static bool _delete(Tree **tree, int key, bool *unbalanced)
{
    bool ret;
    Tree *node;
    if (!*tree)
        return *unbalanced = false;
    else if (key < (*tree)->item.key) {
        ret = _delete(&(*tree)->lchild, key, unbalanced);
        if (*unbalanced)
            rebalance(tree, unbalanced);
        return ret;
    }
    else if (key > (*tree)->item.key) {
        ret = _delete(&(*tree)->rchild, key, unbalanced);
        if (*unbalanced)
            rebalance(tree, unbalanced);
        return ret;
    }
    else {
        node = *tree;
        if (node->lchild && node->rchild) {
            transplant(&node->lchild, tree, unbalanced);
            if (*unbalanced)
                rebalance(tree, unbalanced);
        }
        else {
            *tree = node->lchild ? node->lchild : node->rchild;
            *unbalanced = true;
        }
        free(node);
        return true;
    }
}
bool delete(Tree **tree, int key)
{
    bool unbalanced;
    return _delete(tree, key, &unbalanced);
}

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
    if (root != NULL)
        _printTree(root, root, 0);
    else
        printf("EMPTY\n");
}
