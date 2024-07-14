/* threaded binary tree
 * 20200201
 * root는 더미 값, lchild로 원래의 루트 연결, rchild는 자기 자신 향하는데 rthread는 false
 * + 강의노트 마지막 보면 inorder와 postorder 두 결과를 이용하여 원래의 트리를 복원하는 방법 있음
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct threadedTree {
    bool lthread;
    struct threadedTree *lchild;
    char data;
    struct threadedTree *rchild;
    bool rthread;   // true면 rchild가 thread
} ThreadedTree;

ThreadedTree *insucc(ThreadedTree *tree)
{
    if (!tree->rthread) {
        for (tree = tree->rchild; !tree->lthread; tree = tree->lchild);
        return tree;
    }
    else
        return tree->rchild;
    // root의 rthread는 false가 되어야 한다.
}

void tinorder(ThreadedTree *tree)
{
    ThreadedTree *root;
    root = tree;
    while (true) {
        tree = insucc(tree);
        if (tree == root)
            break;
        printf("%3c", tree->data);
    }
}

void insertRight(ThreadedTree *s, ThreadedTree *r)
{
    ThreadedTree *suc;
    // lchild는 parent를 향하고
    r->lthread = true;
    r->lchild = s;
    // parent의 rchild 관련 속성은 물려받음
    r->rthread = s->rthread;
    r->rchild = s->rchild;
    // 그리고 parent의 rchild를 새로운 노드를 향하도록 하며
    s->rthread = false;
    s->rchild = r;
    // 마지막으로 parent의 원래 rchild가 normal link였다면 parent의 원래 다음 중위 순회 대상의 lchild 또한 새로운 노드를 향함
    if (!r->rthread) {
        suc = insucc(r);
        suc->lchild = r;
    }
}
// left는 반대