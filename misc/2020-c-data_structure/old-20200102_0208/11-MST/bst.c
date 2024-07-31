#include <stdlib.h>

static typedef enum {false, true} bool;

typdef struct bin_tree {
    int key;
    struct bin_tree *left, *right;
} BinTree;

bool search(BinTree *node, int key)
{
    while (node) {
        if (key == node->key)
            return true;
        key = key < node->key ? node->left : node->right;
    }
    return false;
}

static BinTree *pos_search(BinTree *node, int key)
{
    BinTree *parent = NULL;
    while (node) {
        if (key == node->key)
            return NULL;
        node = key < (parent = node)->key ? node->left : node->right;
    }
    return parent;
}

void insert(BinTree **tree, int key)
{
    BinTree *node, *parent;
    parent = pos_search(*tree, key);
    if (parent || *tree) {
        node = malloc(sizeof(*node));
        node->key = key;
        node->left = node->right = NULL;
        if (!*tree)
            *tree = node;
        else {
            if (key < parent->key)
                parent->left = node;
            else
                parent->right = node;
        }
    }
}

void delete(BinTree **tree, int key)
{
    BinTree *node, *parent = NULL;
    BinTree *temp, *temp_parent = NULL; 
    node = *tree;
    while (node) {
        if (key == node->key)
            break;
        node = key < (parent = node)->key ? node->left : node->right;
    }
    if (!node)
        return;
    if (node->left && node->right) {
        for (temp = node->left; temp; temp = (temp_parent = temp)->right);
        if (temp_parent) {
            temp_parent->right = temp->left;
            temp->left = node->left;
        }
        temp->right = node->right;
    }
    else
        temp = node->left ? node->left : node->right;
    if (!*tree)
        *tree = node;
    else {
        if (key < parent->key)
            parent->left = temp;
        else
            parent->right = temp;
    }
}