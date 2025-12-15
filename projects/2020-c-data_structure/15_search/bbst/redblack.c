/* red-black tree
 * 20200210
 * NULL을 NIL로 바꾸는 것 주의
 * colorRoot(), recolor(), rotate(), doubleRed() (insertion), heightDecreased() (deletion), Tree **unbalancedAt
 * unbalancedAt 먼저 확인하고 rebalance 함수로 넘어간다. (가지 치기 위해서)
 * insertion 시 바로 위의 노드가 red인지 확인해야 하므로 매개 변수로 parent 넘기고, 다음과 같이 확인 -> *unbalancedAt = (parent->color == RED) ? *tree : NULL;
 * doubleRed()는 parent, unbalancedAt 넘기고 키 값으로 상대적 위치 확인. rebalance 후 다시 다음과 같이 확인 -> *at = ((*tree)->color == RED && parent->color == RED) ? *tree : NULL;
 * deletion 시 대체된 노드가 NIL일 수 있으므로 키 값으로 비교하면 안 됨. LEFT, RIGHT로
 * heightDecreased()는 대체된 노드가 NIL일 수 있으므로 키 값으로 비교하면 안 됨. 대신 대체된 노드의 parent 위치에서 rebalance 수행하므로 dir, unbalancedAt 넘긴다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
} Element;

typedef enum {RED = -1, BLACK = 1} Color;

typedef struct tree {
    Element item;
    Color color;
    struct tree *lchild, *rchild;
} Tree;

#define NIL &nil
Tree nil = {.item = {.key = -1}, .color = BLACK, .lchild = NULL, .rchild = NULL};

/* balancing functions */

static void colorRoot(Tree *root)
{
    root->color = BLACK;
}

static void recolor(Tree *tree, Tree *except)
{
    if (tree != except && tree != NIL) {
        tree->color *= -1;
        recolor(tree->lchild, except);
        recolor(tree->rchild, except);
    }
}

enum {LEFT = -1, RIGHT = 1};
enum {SINGLE, DOUBLE};
static void rotate(Tree **tree, int dir, int count)
{
    Tree *parent, *child;
    Color c;
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
    SWAP(parent->color, child->color, c);
    *tree = child;
}

static void doubleRed(Tree **tree, Tree *parent, Tree **at)
{
    Tree *uncle;
    if ((*tree)->color == BLACK) {
        if ((*tree)->item.key < (*at)->item.key) {
            uncle = (*tree)->lchild;
            if (uncle->color == RED)
                recolor(*tree, *at);
            else
                rotate(tree, LEFT, (*at == (*tree)->rchild->rchild) ? SINGLE : DOUBLE);
        }
        else {
            uncle = (*tree)->rchild;
            if (uncle->color == RED)
                recolor(*tree, *at);
            else
                rotate(tree, RIGHT, (*at == (*tree)->lchild->lchild) ? SINGLE : DOUBLE);
        }
        *at = ((*tree)->color == RED && parent->color == RED) ? *tree : NULL;   //
    }
}

static void heightDecreased(Tree **tree, int dir, Tree **at)
{
    Color c;
    Tree **parent, **sibling;
    parent = tree;
    if (dir == RIGHT) { //
        sibling = &(*tree)->lchild;
        
        if ((*sibling)->color == RED) {
            // case 2
            rotate(parent, RIGHT, SINGLE);
            parent = &(*parent)->rchild;
            sibling = &(*parent)->lchild;
            // -> 4, 5, 6
        }
        else if ((*parent)->color == BLACK && (*sibling)->lchild->color == BLACK && (*sibling)->rchild->color == BLACK) {
            // case 3
            (*sibling)->color = RED;
            *at = *parent;
            return; // -> recursion
        }
        // case 4
        if ((*parent)->color == RED && (*sibling)->lchild->color == BLACK && (*sibling)->rchild->color == BLACK) {
            SWAP((*parent)->color, (*sibling)->color, c);
            *at = NULL;
            return;
        }
        // case 5
        if ((*sibling)->lchild->color == BLACK && (*sibling)->rchild->color == RED)
            rotate(sibling, LEFT, SINGLE);
            // -> 6
        // case 6
        rotate(parent, RIGHT, SINGLE);
        (*parent)->lchild->color = BLACK;

    }
    else {
        sibling = &(*tree)->rchild;

        if ((*sibling)->color == RED) {
            // case 2
            rotate(parent, LEFT, SINGLE);
            parent = &(*parent)->lchild;
            sibling = &(*parent)->rchild;
            // -> 4, 5, 6
        }
        else if ((*parent)->color == BLACK && (*sibling)->rchild->color == BLACK && (*sibling)->lchild->color == BLACK) {
            // case 3
            (*sibling)->color = RED;
            *at = *parent;
            return; // -> recursion
        }
        // case 4
        if ((*parent)->color == RED && (*sibling)->rchild->color == BLACK && (*sibling)->lchild->color == BLACK) {
            SWAP((*parent)->color, (*sibling)->color, c);
            *at = NULL;
            return;
        }
        // case 5
        if ((*sibling)->rchild->color == BLACK && (*sibling)->lchild->color == RED)
            rotate(sibling, RIGHT, SINGLE);
            // -> 6
        // case 6
        rotate(parent, LEFT, SINGLE);
        (*parent)->rchild->color = BLACK;
    }
}

/* external functions */

void init(Tree **root)
{
    *root = NIL;    //
}
bool empty(Tree *root)
{
    return root == NIL; //
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

static bool _insert(Tree **tree, Tree *parent, Element e, Tree **unbalancedAt)
{
    bool ret;
    if (*tree == NIL) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NIL;
        (*tree)->color = RED;
        *unbalancedAt = (parent->color == RED) ? *tree : NULL;  //
        return true;
    }
    else if (e.key < (*tree)->item.key) {
        ret = _insert(&(*tree)->lchild, *tree, e, unbalancedAt);
        if (*unbalancedAt)
            doubleRed(tree, parent, unbalancedAt);
        return ret;
    }
    else if (e.key > (*tree)->item.key) {
        ret = _insert(&(*tree)->rchild, *tree, e, unbalancedAt);
        if (*unbalancedAt)
            doubleRed(tree, parent, unbalancedAt);
        return ret;
    }
    else {
        *unbalancedAt = NULL;
        return false;
    }
}
bool insert(Tree **tree, Element e)
{
    bool ret;
    Tree *unbalancedAt;
    ret = _insert(tree, NIL, e, &unbalancedAt);
    colorRoot(*tree);
    return ret;
}

static void transplant(Tree **tree, Tree **dst, Tree **unbalancedAt)
{
    Tree *src;
    if ((*tree)->rchild != NIL) {
        transplant(&(*tree)->rchild, dst, unbalancedAt);
        if (*unbalancedAt)
            heightDecreased(tree, RIGHT, unbalancedAt);
    }
    else {
        src = *tree;
        *unbalancedAt = (src->color == BLACK && src->lchild->color == BLACK) ? src->lchild : NULL;  //
        src->lchild->color = BLACK; //
        src->color = (*dst)->color;
        if (src != (*dst)->lchild) {
            *tree = src->lchild;
            src->lchild = (*dst)->lchild;
        }
        src->rchild = (*dst)->rchild;
        *dst = src;
    }
}
static bool _delete(Tree **tree, int key, Tree **unbalancedAt)
{
    bool ret;
    Tree *node;
    if (*tree == NIL)
        return false;
    else if (key < (*tree)->item.key) {
        ret = _delete(&(*tree)->lchild, key, unbalancedAt);
        if (*unbalancedAt)
            heightDecreased(tree, LEFT, unbalancedAt);
        return ret;
    }
    else if (key > (*tree)->item.key) {
        ret = _delete(&(*tree)->rchild, key, unbalancedAt);
        if (*unbalancedAt)
            heightDecreased(tree, RIGHT, unbalancedAt);
        return ret;
    }
    else {
        node = *tree;
        if (node->lchild != NIL && node->rchild != NIL) {
            transplant(&node->lchild, tree, unbalancedAt);
            if (*unbalancedAt)
                heightDecreased(tree, LEFT, unbalancedAt);
        }
        else {
            *tree = (node->lchild != NIL) ? node->lchild : node->rchild;
            *unbalancedAt = (node->color == BLACK && (*tree)->color == BLACK) ? *tree : NULL;   //
            (*tree)->color = BLACK; //
        }
        free(node);
        return true;
    }
}
bool delete(Tree **tree, int key)
{
    bool ret;
    Tree *unbalancedAt;
    ret = _delete(tree, key, &unbalancedAt);
    colorRoot(*tree);
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
void printTree(Tree *root)
{
    if (root != NIL)
        _printTree(root, root, 0);
    else
        printf("EMPTY\n");
}