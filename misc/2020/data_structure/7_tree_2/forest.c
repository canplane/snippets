/* forest : a set of n >= 0 disjoint trees
 * 20200212
 * k-ary tree의 자료 구조를 이용하면 루트 노드의 right sibling로 가리킬 수 있음
 * disjoint set이나 루트 노드에 대한 linked list로 구현해도 될 듯
 */

typedef struct {
    int key;
} Element;

typedef struct tree {
    Element e;
    struct tree *lchild, *rsibling;
} Tree;

/* or */

typedef struct forest {
    struct tree *root;
    struct forest *next;
} Forest;