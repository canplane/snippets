#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct tree {
    int key;
    struct node *left, *right;
} Tree;

bool search(Tree **tree, int key)
{
    Tree *node = *tree;
    while (node) {
        if (key == node->key)
            return true;
        node = key < node->key ? node->left : node->right;
    }
    return false;
}

static Tree *pos_search(Tree **tree, int key)
{
    Tree *node = *tree, *parent = NULL;
    while (node) {
        if (key == node->key)
            return NULL;
        node = key < (parent = node)->key ? node->left : node->right;
    }
    return parent;
}

/*
bool insert(Tree **tree, element e)
{
    if (!*tree) {
        *tree = malloc(sizeof(Tree));
        (*tree)->item = e;
        (*tree)->lchild = (*tree)->rchild = NULL;
        return true;
    }
    else if (e.key < (*tree)->item.key) {
        return insert(&(*parent)->lchild, e);
    }
    else if (e.key > (*tree)->item.key) {
        return insert(&(*parent)->rchild, e);
    }
    else {
        return false;
    }
}
*/

bool insert(Tree **tree, int key)
{
    Tree *node, *parent = NULL;
    if (!*tree || (parent = pos_search(tree, key))) {
        node = malloc(sizeof(*node));
        node->key = key;
        node->left = node->right = NULL;
        if (parent) {
            if (key < parent->key)
                parent->left = node;
            else
                parent->right = node;
        }
        else
            *tree = node;
        return true;
    }
    else
        return false;
}

bool delete(Tree **tree, int key)
{
    Tree *node = *tree, *parent = NULL, *temp, *temp_parent = NULL;
    while (node) {
        if (key == node->key)
            break;
        node = key < (parent = node)->key ? node->left : node->right;
    }
    if (!node)
        return false;
    if (node->left && node->right) {
        for (temp = node->left; temp->right; temp = (temp_parent = temp)->right);
        if (temp_parent) {
            temp_parent->right = temp->left;
            temp->left = node->left;
        }
        temp->right = node->right;
    }
    else
        temp = node->left ? node->left : node->right;
    if (parent) {
        if (parent->left == node)
            parent->left = temp;
        else
            parent->right = temp;
    }
    else
        *tree = temp;
    free(node);
    return true;
}