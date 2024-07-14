/* merge sort
 * 20200206
 * mergeSort()는 dst, src, s를 mergePass()에 전달하고, mergePass()는 s에 따라 배열을 나누고 left, mid(왼쪽 배열 마지막 인덱스), right(오른쪽 배열 마지막 인덱스)를 merge()에 전달
 * stable sort, not in-place sort
 * 최악의 경우에도 O(nlgn)
 * external sort에 유용.
 * 예시) 900MB의 데이터를 200MB의 RAM을 사용하여 정렬할 때, 100MB씩 읽어들여 quicksort와 같이 일반적인 알고리즘 사용하여 정렬한 후 정렬된 데이터를 디스크에 쓴다.
 * 9개 파일에서 처음부터 10MB씩 메모리(입력 버퍼)에 로딩하고 10MB의 출력을 위한 버퍼도 만들어 둔 후, 9-way merge를 수행하여 결과를 출력 버퍼에 쓴다. 버퍼가 차면 파일에 쓰고, 9개의 입력 버퍼가 비워지면 다음 10MB를 읽는다.
 */

#include <stdio.h>
#include "data.h"

void merge(Element dst[], Element src[], int left, int mid, int right)
{
    int i, j, k;
    for (k = i = left, j = mid + 1; i <= mid && j <= right;)
        dst[k++] = (src[i].key <= src[j].key) ? src[i++]: src[j++]; // < 면 unstable
    while (i <= mid)
        dst[k++] = src[i++];
    while (j <= right)
        dst[k++] = src[j++];
}

void mergePass(Element dst[], Element src[], int size, int s)
{
    int i;
    for (i = 0; i + 2*s - 1 < size; i += 2*s)
        merge(dst, src, i, i + s - 1, i + 2*s - 1);
    if (i + s < size)
        merge(dst, src, i, i + s - 1, size - 1);
    else
        merge(dst, src, i, size - 1, size - 1);
}

void mergeSort(Element a[], int size)
{
    Element extra[size];
    int s;
    s = 1;
    while (s < size) {
        mergePass(extra, a, size, s);
        s *= 2;
        mergePass(a, extra, size, s);
        s *= 2;
    }
}

/* main */

#define DATASZ 16
int main()
{
    Element data[DATASZ];
    setData(data, DATASZ, 1, 26, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);
    
    mergeSort(data, DATASZ);

    printData(data, DATASZ);
    return 0;
}
