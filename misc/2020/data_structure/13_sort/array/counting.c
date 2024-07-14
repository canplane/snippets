/* counting sort
 * 20200207
 * 각 숫자가 몇 번 포함되어 있는지 센다. count 배열의 각 값을 누적 인덱스로 바꾼다. (count[i] += count[i - 1])
 * i 값이 들어갈 마지막 인덱스의 다음 인덱스가 count[i]이므로 stable을 위해 뒤부터 정렬해 나간다.
 * 대부분의 상황에서 메모리 낭비 야기할 수 있음
 * O(k + n + k + n) = O(n + k) (k는 최댓값)
 * not comparison sort, stable sort, not in-place sort
 */

#include <stdio.h>
#include "data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void countingSort(Element dst[], Element src[], int size, int maxnum)
{
    int i;
    int count[maxnum + 1];
    for (i = 0; i < maxnum + 1; i++)
        count[i] = 0;
    
    for (i = 0; i < size; i++)
        count[src[i].key]++;
    for (i = 1; i < maxnum + 1; i++)
        count[i] += count[i - 1];
    
    for (i = size - 1; i >= 0; i--)
        dst[--count[src[i].key]] = src[i];
}

/* main */

#define DATASZ 16
#define MAXNUM 100
int main()
{
    Element input[DATASZ], output[DATASZ];
    setData(input, DATASZ, 5, 5, 3, 4, 5, 1, 0, 4, 1, 3, 0, 2, 4, 2, 3, 0);
    
    countingSort(output, input, DATASZ, MAXNUM);

    printData(output, DATASZ);
    return 0;
}