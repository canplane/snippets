/* threaded binary tree
 * 20200128_0428
 * + 강의노트 마지막 보면 inorder와 postorder 두 결과를 이용하여 원래의 트리를 복원하는 방법 있음
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct threadedTree {
    bool lthread;
    struct threadedTree *lchild;
    char data;
    struct threadedTree *rchild;
    bool rthread;   // true면 rchild가 thread
} ThreadedTree;
// root는 더미 값, lchild로 원래의 루트 연결, rchild는 자기 자신 향하는데 rthread는 false

/* inorder */

ThreadedTree *insucc(ThreadedTree *tree)
{
    ThreadedTree *suc = tree->rchild;
    if (!tree->rthread) {
        while (!tree->lthread) {
            suc = suc->lchild;
        }
    }
    // root의 rthread는 false가 되어야 한다.
    return suc;
}

void tinorder(ThreadedTree *root)
{
    ThreadedTree *tree = root;
    while (true) {
        tree = insucc(tree);
        if (tree == root)
            break;
        printf("%3c", tree->data);
    }
}

/* insert */

void insertRight(ThreadedTree *parent, ThreadedTree *child)
{
    ThreadedTree *suc_old;
    // parent의 rchild 관련 속성은 물려받고
    child->rthread = parent->rthread;
    child->rchild = parent->rchild;
    // lchild는 parent를 향한다
    child->lthread = true;
    child->lchild = parent;
    // 그리고 parent의 rchild를 새로운 노드를 향하도록 한다
    parent->rthread = false;
    parent->rchild = child;
    // 마지막으로 parent의 원래 rchild가 normal link였다면 parent의 원래 다음 중위 순회 대상의 lchild 또한 새로운 노드를 향한다.
    if (!child->rthread) {
        suc_old = insucc(child);
        suc_old->lchild = child;
    }
}
// left는 반대