/* O(N^2) sorts (insertion, bubble, selection)
 * 20200206
 * size - 1번 검사하므로 따라서 i 범위 내 정수는 size - 1개
 * selection sort는 unstable
 */

#include <stdio.h>
#include "data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 강의 노트에서는 a[1] ~ a[size]를 데이터 구간으로 두었으나 여기서는 그렇게 하지 않는다. a[0] 대신 tmp 이용
// stable
void insertionSort(Element a[], int size)
{
    int i, j;
    Element tmp;
    for (i = 1; i < size; i++) {
        tmp = a[i];
        for (j = i - 1; j >= 0 && a[j].key > tmp.key; j--)
            a[j + 1] = a[j];
        a[j + 1] = tmp;
    }
}

// stable
void bubbleSort(Element a[], int size)
{
    int i, j;
    Element tmp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < (size - 1) - i; j++)
            if (a[j].key > a[j + 1].key)
                SWAP(a[j], a[j + 1], tmp);
    }
}

// unstable
void selectionSort(Element a[], int size)
{
    int i, j, min;
    Element tmp;
    for (i = 0; i < size - 1; i++) {
        min = i;
        for (j = i + 1; j < size; j++)
            if (a[j].key < a[min].key)
                min = j;
        SWAP(a[i], a[min], tmp);
    }
}

/* main */

#define DATASZ 16
int main()
{
    Element data[DATASZ];
    setData(data, DATASZ, 1, 26, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);
    
    //insertionSort(data, DATASZ);
    //bubbleSort(data, DATASZ);
    selectionSort(data, DATASZ);

    printData(data, DATASZ);
    return 0;
}