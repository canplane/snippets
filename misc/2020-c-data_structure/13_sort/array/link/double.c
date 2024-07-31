/* doubly linked list sort, swap
 * 20200207
 * radix sort 등의 not in-place sort에서 extra 배열 생성하는 대신, 간이 구현한 linked list로 정렬 순서 참조만 하고 마지막에 배열을 변경할 때 이용됨
 * 각 record 크기가 클 때 발생하는 오버헤드 방지
 * swap 대상이 인접할 때 꼬이지 않게 주의. left_i, left_j, right_i, right_j에서 먼저 링크 바꾸고 대상들 swap
 * 각 리스트의 끝은 -1로 둔다.
 */

#include <stdio.h>
#include "../data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

/*
void printDoubleList(Element a[], int next[], int prev[], int size)
{
    int i;
    printData(a, size);
    printf("next : ");
    for (i = 0; i < size; i++)
        printf("%d ", next[i]);
    printf(", prev : ");
    for (i = 0; i < size; i++)
        printf("%d ", prev[i]);
    printf("\n");
}
*/

// 직접 구현한 코드, 일반적인 swap 기능 구현
void doubleListSwap(Element a[], int next[], int prev[], int i, int j)
{
    int left, right;
    Element tmp;
    int t;

    // adjacent일 때 영향받는 것들끼리 묶음
    left = prev[i], right = next[j];
    if (left != -1)
        next[left] = j;
    if (right != -1)
        prev[right] = i;
    left = prev[j], right = next[i];
    if (left != -1)
        next[left] = i;
    if (right != -1)
        prev[right] = j;
    SWAP(a[i], a[j], tmp);
    SWAP(prev[i], prev[j], t);
    SWAP(next[i], next[j], t);
}
void doubleListSort(Element a[], int next[], int size, int head)
{
    int cur, i;
    int prev[size], left, right;

    for (left = -1, cur = head; cur != -1; left = cur, cur = next[cur])
        prev[cur] = left;
    
    for (i = 0; i < size; i++) {
        //printDoubleList(a, next, prev, size);
        if (i != head)
            doubleListSwap(a, next, prev, i, head);
        head = next[i];
    }
}

// 강의 노트에 주어진 코드, 직접 구현한 코드에서 소거해서 구현하는 것이 좋음
void listSort1(Element a[], int next[], int size, int head)
{
    int cur, i;
    int prev[size], left, right;
    Element tmp;
    int t;

    for (left = -1, cur = head; cur != -1; left = cur, cur = next[cur])
        prev[cur] = left;
    
    for (i = 0; i < size; i++) {
        if (i != head) {
            // head 노드는 이제 안 쓸 것이기 때문에 head를 향하는 링크(prev[head], next[head])는 신경 안 써도 됨 (doubleListSort()는 next[], prev[]를 보존하며 정렬하는 코드)
            next[prev[i]] = head;
            if (next[i] != -1)
                prev[next[i]] = head;
            SWAP(a[i], a[head], tmp);
            SWAP(prev[i], prev[head], t);
            SWAP(next[i], next[head], t);
        }
        head = next[i];
    }
}

/* main */
/*
#define DATASZ 10
int main()
{
    Element data[DATASZ];
    int link[] = {8, 5, -1, 1, 2, 7, 4, 9, 6, 0}, head = 3;
    //int link[] = {2, 4, 1, 0, -1}, head = 3;
    //setData(data, DATASZ, 1, 3, 2, 0, 4);
    setData(data, DATASZ, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19);

    doubleListSort(data, link, DATASZ, head);
    //listSort1(data, link, DATASZ, head);

    printData(data, DATASZ);
    return 0;
}
*/
