/* binary tree traversal : inorder(LVR), preorder(VLR), postorder(LRV), level-order(breath-first)
 * 20200130
 * graph traversal에서는 preorder -> dfs, level-order -> bfs
 * postorder는 right 기준으로 preorder한 결과의 역순과 같음
 */

#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "deque.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void inorder(Tree *tree)
{
    if (tree) {
        inorder(tree->lchild);
        printf("%c ", tree->item.key);
        inorder(tree->rchild);
    }
}
void preorder(Tree *tree)
{
    if (tree) {
        printf("%c ", tree->item.key);
        preorder(tree->lchild);
        preorder(tree->rchild);
    }
}
void postorder(Tree *tree)
{
    if (tree) {
        postorder(tree->lchild);
        postorder(tree->rchild);
        printf("%c ", tree->item.key);
    }
}

void levelorder(Tree *tree)
{
    enqueue(tree);
    while (true) {
        if (empty())
            break;
        tree = front(), dequeue();
        printf("%c ", tree->item.key);
        if (tree->lchild)
            enqueue(tree->lchild);
        if (tree->rchild)
            enqueue(tree->rchild);
    }
}

/* traversal (iterative) */

void iterInorder(Tree *tree)
{
    init();
    while (true) {
        for (; tree; tree = tree->lchild)
            push(tree);
        if (empty())
            break;
        tree = top(), pop();
        printf("%c ", tree->item.key);
        tree = tree->rchild;
    }
}
void iterPreorder(Tree *tree)
{
    init();
    while (true) {
        for (; tree; tree = tree->lchild) {
            printf("%c ", tree->item.key);
            push(tree);
        }
        if (empty())
            break;
        tree = top(), pop();
        tree = tree->rchild;
    }
}
void iterPostorder(Tree *tree)
{
    char str[MAXSZ] = {0}, *p, tmp;
    int i;

    p = str;
    init();
    while (true) {
        // right 기준으로 preorder
        for (; tree; tree = tree->rchild) {
            p += sprintf(p, " %c", tree->item.key);
            push(tree);
        }
        if (empty())
            break;
        tree = top(), pop();
        tree = tree->lchild;
    }
    // 역순 출력
    for (i = 0; i < (p - str) / 2; i++)
        SWAP(*(str + i), *(p - i - 1), tmp);
    printf("%s", str);
}

/* main */

int main()
{
    Element e;
    Tree *root;

    e.key = 'A', root = newTree(e, NULL, NULL);
    e.key = 'B', root->lchild = newTree(e, NULL, NULL);
    e.key = 'C', root->rchild = newTree(e, NULL, NULL); 
    e.key = 'D', root->lchild->lchild = newTree(e, NULL, NULL);
    e.key = 'E', root->lchild->rchild = newTree(e, NULL, NULL);
    e.key = 'F', root->rchild->lchild = newTree(e, NULL, NULL);
    e.key = 'G', root->rchild->rchild = newTree(e, NULL, NULL);
    e.key = 'H', root->lchild->lchild->lchild = newTree(e, NULL, NULL);
    e.key = 'I', root->lchild->lchild->rchild = newTree(e, NULL, NULL);
    
    printf("inorder : ");
    iterInorder(root);
    printf("\n");

    printf("preorder : ");
    iterPreorder(root);
    printf("\n");

    printf("postorder : ");
    iterPostorder(root);
    printf("\n");

    printf("level-order : ");
    levelorder(root);
    printf("\n");

    return 0;
}