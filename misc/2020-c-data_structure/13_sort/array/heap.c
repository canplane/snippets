/* heap sort
 * 20200206
 * max heap으로 변환한 후, 하나씩 pop하여 뒤부터 정렬해 나간다. (heapify, push 모두 O(nlgn)이나 heapify가 더 효율적)
 * heapify()는 pop()에서 heap[root] = heap[size--]한 이후의 알고리즘과 같다. 모든 subtree는 이미 heap 구조를 만족한다고 가정하여 한 루트 노드에 대해서만 수행하도록 구현할 것
 * unstable sort, in-place sort, O(nlgn)
 * bst 만들고 inorder traversal하는 tree sort도 있음. 근데 그것보단 heap sort가 나을 듯.
 */

#include <stdio.h>
#include "data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void heapify(Element heap[], int root, int size)
{
    int i;
    Element e;
    e = heap[root];
    for (i = 2 * root; i <= size; i *= 2) {
        if (i + 1 <= size && heap[i + 1].key > heap[i].key)
            i++;
        if (heap[i].key > e.key)
            heap[i / 2] = heap[i];
        else
            break;
    }
    heap[i / 2] = e;
}

void heapSort(Element a[], int size)
{
    int i;
    Element tmp;
    for (i = size / 2; i > 0; i--)
        heapify(a - 1, i, size);    // a - 1으로 넘기는 게 이전에 구현한 heap 구조에 친화적
    for (i = size; i > 1; i--) {
        SWAP(a[0], a[i - 1], tmp);
        heapify(a - 1, 1, i - 1);
    }
}

/* main */

#define DATASZ 16
int main()
{
    Element data[DATASZ];
    setData(data, DATASZ, 1, 26, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);
    
    heapSort(data, DATASZ);

    printData(data, DATASZ);
    return 0;
}
