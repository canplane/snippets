/* left child - right sibling representation
 * 20200130
 * k-ary tree 표현할 때 쓸 수 있음 (아니면 array representation)
 * binary tree와 같이 lchild, rchild 구별할 필요가 없으므로 left부터 시작
 * 자식 link 만드는 방법에서 헤더 리스트에 대한 인덱스를 int vertex로 접근하면 그래프 인접 리스트와 같고, 따로 포인터를 두어 연결하면 아래와 같은 구조가 된다.
 */

typedef struct {
    int key;
} Element;

typedef struct tree {
    Element item;
    struct tree *lchild, *rsibling;
} Tree;