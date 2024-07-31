/* m-way B-Tree (insertion만 구현)
 * 20200211
 * 기존의 BST 삽입, 삭제 절차 이후 rebalance() 추가
 * findPos(), add(), divide(), bool *unbalanced
 * 새로운 노드는 루트 위치에서만 생성해야 함
 * items[], children[] 사이즈를 1개 더 할당해서 쉽게 하자. (원래는 각각 WAYS - 1, WAYS)
 * parent, parentIdx 넘기고 자식 위치에서 add() 수행. (단말 노드 NULL일 때 수행하기 위해)
 * parent의 items 사이즈가 m개가 되면 *unbalanced = true로 바꾼다. parent에서 unbalanced 확인하고 divide 수행
 * 노드에 키 add 시 원래 키, 자식들 오른쪽으로 미는데 맨 왼쪽 자식는 그냥 냅두고 그 오른쪽 자식은 매개 변수로 지정한다.
 * findPos는 키가 일치하면 매개 변수로 받은 곳에 해당 인덱스 넘기고 true, 키가 없으면 들어갈 위치의 오른쪽 위치 넘기고 false
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char key;
} Element;

#define WAYS 5
typedef struct bTree {
    int size;
    Element items[WAYS];
    struct bTree *children[WAYS + 1];
} BTree;

/* balancing function */

static bool findPos(BTree *tree, char key, int *idx)
{
    int i;
    bool ret;
    ret = false;
    for (i = 0; i < tree->size; i++) {
        if (key > tree->items[i].key)
            continue;
        ret = (key == tree->items[i].key);
        break;
    }
    *idx = i;
    return ret;
}

static void add(BTree *node, int idx, Element e, BTree *rlink)
{
    int i;
    for (i = node->size; i > idx; i--) {
        node->items[i] = node->items[i - 1];
        node->children[i + 1] = node->children[i];
    }
    node->items[idx] = e;
    node->children[idx + 1] = rlink;
    node->size++;
}

static void divide(BTree *parent, int parentIdx)
{
    int i, mid;
    BTree *ltree, *rtree;
    ltree = parent->children[parentIdx];
    rtree = malloc(sizeof(BTree)), memset(rtree, 0, sizeof(BTree));

    mid = WAYS / 2;
    ltree->size = mid, rtree->size = (WAYS - 1) - mid;

    rtree->children[0] = ltree->children[mid + 1];
    for (i = mid + 1; i < WAYS; i++) {
        rtree->items[i - (mid + 1)] = ltree->items[i];
        rtree->children[i - mid] = ltree->children[i + 1];
    }
    
    add(parent, parentIdx, ltree->items[mid], rtree);
}

/* external functions */

void init(BTree **root)
{
    *root = NULL;
}
bool empty(BTree *root)
{
    return !root;
}

Element *search(BTree *tree, char key)
{
    int idx;
    if (!tree) {
        return NULL;
    }
    else if (!findPos(tree, key, &idx)) {
        return search(tree->children[idx], key);
    }
    else {
        return &tree->items[idx];
    }
}

static bool _insert(BTree **tree, BTree *parent, int parentIdx, Element e, bool *unbalanced)
{
    bool ret;
    BTree *node;
    int idx;
    if (!*tree) {
        if (!parent) {
            node = malloc(sizeof(BTree)), memset(node, 0, sizeof(BTree));
            add(node, 0, e, NULL);
            *tree = node;
            *unbalanced = false;
        }
        else {
            add(parent, parentIdx, e, NULL);
            *unbalanced = (parent->size == WAYS);
        }
        return true;
    }
    else if (!findPos(*tree, e.key, &idx)) {
        ret = _insert(&(*tree)->children[idx], *tree, idx, e, unbalanced);
        if (*unbalanced) {
            if (!parent) {
                node = malloc(sizeof(BTree)), memset(node, 0, sizeof(BTree));
                node->children[0] = *tree;
                divide(node, 0);
                *tree = node;
                *unbalanced = false;
            }
            else {
                divide(parent, parentIdx);
                *unbalanced = (parent->size == WAYS);
            }
        }
        return ret;
    }
    else
        return *unbalanced = false;
}
bool insert(BTree **tree, Element e)
{
    bool unbalanced;
    return _insert(tree, NULL, -1, e, &unbalanced);
}

void _printTree(BTree *tree, BTree *root, char lkey, char rkey)
{
    int i;
    if (tree) {
        if (tree == root)
            printf("root : ");
        else {
            if (lkey == -1)
                printf("left child of %c : ", rkey);
            else if (rkey == -1)
                printf("right child of %c : ", lkey);
            else
                printf("child between %c and %c : ", lkey, rkey);
        }
        for (i = 0; i < tree->size; i++)
            printf("%c ", tree->items[i].key);
        printf("\n");
        for (i = 0; i < tree->size + 1; i++) {
            if (i == 0)
                _printTree(tree->children[i], root, -1, tree->items[i].key);
            else if (i == tree->size)
                _printTree(tree->children[i], root, tree->items[i - 1].key, -1);
            else
                _printTree(tree->children[i], root, tree->items[i - 1].key, tree->items[i].key);
        }
    }
}
void printTree(BTree *root)
{
    _printTree(root, root, -1, -1);   
}
