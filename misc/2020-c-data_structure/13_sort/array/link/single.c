/* singly linked list sort
 * 20200207
 * 강의 노트로 주어진 코드에 들어 있는 알고리즘에 맞춰 구현하는 데 익숙해질 것 (원래의 링크를 활용하는 과정 이용)
 * doubly linked list sort에 비해 비효율적
 */

#include <stdio.h>
#include "../data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

/*
void printSingleList(Element a[], int next[], int size)
{
    int i;
    printData(a, size);
    printf("next : ");
    for (i = 0; i < size; i++)
        printf("%d ", next[i]);
    printf("\n");
}
*/

// 직접 작성한 코드, 매 시도마다 swap 후 prev까지 가서 다시 잇는다. -> 앞에서 오버헤드가 클 것
void singleListSort(Element a[], int next[], int size, int head)
{
    int cur, i;
    Element tmp;
    int t;
    for (i = 0; i < size; i++) {
        if (i != head) {
            SWAP(a[i], a[head], tmp);
            SWAP(next[i], next[head], t);
            for (cur = i; next[cur] != i; cur = next[cur]);
            next[cur] = head;
        }
        head = next[i];
    }
}

// 강의 노트에 주어진 코드, 다음 head를 찾을 때 기존의 링크를 활용한다. -> 뒤에서 오버헤드가 클 것
void listSort2(Element a[], int next[], int size, int head)
{
    int i, q;
    Element tmp;
    for (i = 0; i < size; i++) {
        //printSingleList(a, next, size);
        for (; head < i; head = next[head]);
        q = next[head];
        if (i != head) {
            SWAP(a[i], a[head], tmp);
            next[head] = next[i];
            next[i] = head;
        }
        head = q;
    }
}

/* main */
/*
#define DATASZ 10
int main()
{
    Element data[DATASZ];
    int link[] = {8, 5, -1, 1, 2, 7, 4, 9, 6, 0}, head = 3;
    setData(data, DATASZ, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19);

    //singleListSort(data, link, DATASZ, head);
    listSort2(data, link, DATASZ, head);

    printData(data, DATASZ);
    return 0;
}
*/
