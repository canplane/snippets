/* quick sort (linked list)
 * 20200209
 * right는 원래 right 대상의 다음 노드
 * delete 후 insert하는 대신, void list_rearrange(List *list, Node *dstLeft, Node *node) 구현
 */

#include <stdio.h>
#include "data.h"
#include "list.h"

void quickSort(List *list, Node *left, Node *right)
{
    Node *node, *tmp;
    Node *pivot;
    Element e;
    if (left != right) {
        pivot = left;
        for (node = pivot->next; node != right; node = tmp) {
            tmp = node->next;
            if (node->item.key < pivot->item.key) {
                list_transplant(list, left->prev, node);
                left = node;
            }
        }
        quickSort(list, left, pivot);
        quickSort(list, pivot->next, right);
    }
}

/* main */

#define DATASZ 16
int main()
{
    List list;
    setData(&list, DATASZ, 26, 1, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);

    quickSort(&list, list.head, NULL);

    printData(&list);
    return 0;
}