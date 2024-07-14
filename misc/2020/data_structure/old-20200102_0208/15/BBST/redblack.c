/* 20200127_0817 */

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef enum {false, true} bool;

typedef struct {
    int key;
} Element;

/* Data Types */

typedef enum {BLACK = -1, RED = 1} Color;

typedef struct tree {
    Element item;
    Color color;
    struct tree *lchild, *rchild;
} Tree;

static Tree nil = {{-1}, BLACK, NULL, NULL}, *NIL = &nil;

/* Internal Balancing Functions */

enum {LEFT = -1, RIGHT = 1};
enum {SINGLE, DOUBLE};
static void _rotate(Tree **tree, int dir, int count)
{
    Tree *parent, *child;
    Color tmp;
    parent = *tree;
    if (dir == RIGHT) {
        if (count == DOUBLE) {
            _rotate(&(*tree)->lchild, LEFT, SINGLE);
        }
        child = parent->lchild;
        parent->lchild = child->rchild;
        child->rchild = parent;
    }
    else {
        if (count == DOUBLE) {
            _rotate(&(*tree)->rchild, RIGHT, SINGLE);
        }
        child = parent->rchild;
        parent->rchild = child->lchild;
        child->lchild = parent;
    }
    SWAP(parent->color, child->color, tmp);     // preserves color
    *tree = child;
}

static void _recolor(Tree *tree, Tree *except)
{
    if (tree != NIL && tree != except) {
        tree->color *= -1;
        _recolor(tree->lchild, except);
        _recolor(tree->rchild, except);
    }
}

static void _recolorRoot(Tree *root)
{
    root->color = BLACK;
}

static void _checkAndBalanceRed(Tree **tree, Tree *child, Tree **unbalanced)
{
    Tree *uncle;
    if ((*tree)->color == RED && child->color == RED) {
        *unbalanced = child;
    }
    else if (*unbalanced && (*tree)->color == BLACK) {
        if (child == (*tree)->rchild) {
            uncle = (*tree)->lchild;
            if (uncle->color == BLACK)
                _rotate(tree, LEFT, *unbalanced == child->rchild ? SINGLE : DOUBLE);
            else
                _recolor(*tree, *unbalanced);
        }
        else {
            uncle = (*tree)->rchild;
            if (uncle->color == BLACK)
                _rotate(tree, RIGHT, *unbalanced == child->lchild ? SINGLE : DOUBLE);
            else
                _recolor(*tree, *unbalanced);
        }
        *unbalanced = NULL;
    }
}

static void _checkHeight(Tree *parent, Tree *child, Tree **unbalanced)
{
    if (parent->color == BLACK && child->color == BLACK)
        *unbalanced = child;
    else
        child->color = BLACK;
}

static void _balanceHeight(Tree **tree, Tree **unbalanced)
{
    Tree **parent, *sibling;
    parent = tree;  // case 2에서 원래의 tree 값에 영향 주지 않게 분리
    if (*unbalanced == (*parent)->rchild) {
        sibling = (*parent)->lchild;
        if (sibling->color == RED) {
            // case 2
            _rotate(parent, RIGHT, SINGLE);
            parent = &(*parent)->rchild, sibling = (*parent)->lchild;
            // -> 4, 5, 6
        }
        else if ((*parent)->color == BLACK && sibling->lchild->color == BLACK && sibling->rchild->color == BLACK) {
            // case 3
            sibling->color = RED;
            *unbalanced = *parent;
            return;
            // -> recursion
        }
        if ((*parent)->color == RED && sibling->lchild->color == BLACK && sibling->rchild->color == BLACK) {
            // case 4
            (*parent)->color = BLACK, sibling->color = RED;
            *unbalanced = NULL;
            return;
        }
        if (sibling->lchild->color == BLACK && sibling->rchild->color == RED) {
            // case 5
            _rotate(&(*parent)->lchild, LEFT, SINGLE), sibling = (*parent)->lchild;
            // -> 6
        }
        if (sibling->lchild->color == RED) {
            // case 6
            _rotate(parent, RIGHT, SINGLE), sibling = (*parent)->lchild;
            sibling->color = BLACK;
            *unbalanced = NULL;
            return;
        }
    }
    else {
        sibling = (*parent)->rchild;
        if (sibling->color == RED) {
            // case 2
            _rotate(parent, LEFT, SINGLE);
            parent = &(*parent)->lchild, sibling = (*parent)->rchild;
            // -> 4, 5, 6
        }
        else if ((*parent)->color == BLACK && sibling->rchild->color == BLACK && sibling->lchild->color == BLACK) {
            // case 3
            sibling->color = RED;
            *unbalanced = *parent;
            return;
            // -> recursion
        }
        if ((*parent)->color == RED && sibling->rchild->color == BLACK && sibling->lchild->color == BLACK) {
            // case 4
            (*parent)->color = BLACK, sibling->color = RED;
            *unbalanced = NULL;
            return;
        }
        if (sibling->rchild->color == BLACK && sibling->lchild->color == RED) {
            // case 5
            _rotate(&(*parent)->rchild, RIGHT, SINGLE), sibling = (*parent)->rchild;
            // -> 6
        }
        if (sibling->rchild->color == RED) {
            // case 6
            _rotate(parent, LEFT, SINGLE), sibling = (*parent)->rchild;
            sibling->color = BLACK;
            *unbalanced = NULL;
            return;
        }
    }
}

/* Internal Accessing Functions */

static bool _insert(Tree **tree, Element e, Tree **unbalanced)
{
    bool ret;
    if (*tree == NIL) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NIL;
        (*tree)->color = RED;
        *unbalanced = NULL;
        ret = true;
    }
    else if (e.key < (*tree)->item.key) {
        ret = _insert(&(*tree)->lchild, e, unbalanced);
        if (ret)
            _checkAndBalanceRed(tree, (*tree)->lchild, unbalanced);
    }
    else if (e.key > (*tree)->item.key) {
        ret = _insert(&(*tree)->rchild, e, unbalanced);
        if (ret)
            _checkAndBalanceRed(tree, (*tree)->rchild, unbalanced);
    }
    else {
        ret = false;
    }
    return ret;
}

static void _transplant(Tree **tree, Tree **dst, Tree **unbalanced)
{
    Tree *src;
    if ((*tree)->rchild != NIL) {
        _transplant(&(*tree)->rchild, dst, unbalanced);
        if (*unbalanced)
            _balanceHeight(tree, unbalanced);
    }
    else {
        src = *tree;
        _checkHeight(src, src->lchild, unbalanced);
        if (src != (*dst)->lchild) {
            *tree = src->lchild;
            src->lchild = (*dst)->lchild;
        }
        src->rchild = (*dst)->rchild;
        src->color = (*dst)->color;     // preserves color
        *dst = src;
    }
}

static bool _delete(Tree **tree, int key, Tree **unbalanced)
{
    bool ret;
    Tree *target;
    if (*tree == NIL) {
        ret = false;
    }
    else if (key < (*tree)->item.key) {
        ret = _delete(&(*tree)->lchild, key, unbalanced);
        if (*unbalanced)
            _balanceHeight(tree, unbalanced);
    }
    else if (key > (*tree)->item.key) {
        ret = _delete(&(*tree)->rchild, key, unbalanced);
        if (*unbalanced)
            _balanceHeight(tree, unbalanced);
    }
    else {
        target = *tree;
        if (target->lchild != NIL && target->rchild != NIL) {
            _transplant(&target->lchild, tree, unbalanced);
            if (*unbalanced)
                _balanceHeight(tree, unbalanced);
        }
        else {
            *tree = target->lchild != NIL ? target->lchild : target->rchild;
            _checkHeight(target, *tree, unbalanced);
        }
        free(target);
        ret = true;
    }
    return ret;
}

#define RED_TXT "\x1b[31m"
#define WHITE_TXT "\x1b[0m"
static void _printTree(Tree *tree, Tree *parent, int dir)
{
    if (tree != NIL) {
        if (dir)
            printf("%s%d%s : %s child of %d\n", tree->color == RED ? RED_TXT : WHITE_TXT, tree->item.key, WHITE_TXT, dir == LEFT ? "left" : "right", parent->item.key);
        else
            printf("%s%d%s : root\n", tree->color == RED ? RED_TXT : WHITE_TXT, tree->item.key, WHITE_TXT);
        _printTree(tree->lchild, tree, LEFT);
        _printTree(tree->rchild, tree, RIGHT);
    }
}

/* External Functions */

void init(Tree **tree)
{
    *tree = NIL;
    NIL->lchild = NIL->rchild = *tree;
}

bool empty(Tree *tree)
{
    return tree == NIL;
}

Element *search(Tree *tree, int key)
{
    if (tree == NIL)
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
    bool ret;
    Tree *unbalanced = NULL;
    ret = _insert(tree, e, &unbalanced);
    _recolorRoot(*tree);
    return ret;
}

bool delete(Tree **tree, int key)
{
    bool ret;
    Tree *unbalanced = NULL;
    ret = _delete(tree, key, &unbalanced);
    _recolorRoot(*tree);
    return ret;
}

void printTree(Tree *root)
{
    if (root != NIL)
        _printTree(root, root, 0);
    else
        printf("EMPTY\n");
}