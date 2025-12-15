/* quick sort
 * 20200206
 * 대표적인 분할 정복 알고리즘
 * i : +, j : -, 0
 * pivot은 left에 있으므로 j 값과 무조건 바꿔야 함
 * 평균의 경우 O(nlgn) : T(n) = n + 2T(n/2) = hn + 2^h * T(0) = hn = nlgn
 * 정렬 혹은 역정렬로 배열된 경우엔 O(n^2) : T(n) = n + T(n - 1) (최댓값이나 최솟값을 pivot으로 잡는 경우 좌우로 분할되지 않으므로 분할 정복의 효과가 없음)
 * 이를 방지하기 위해 mid를 pivot으로 삼는다.
 * unstable sort (모든 배열이 -, 0인 경우 pivot이 right로 이동하므로), in-place sort
 */

#include <stdio.h>
#include <stdbool.h>
#include "data.h"

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void quickSort(Element a[], int left, int right)
{
    int mid, i, j;
    Element tmp;
    if (left < right) {
        mid = (left + right) / 2;
        SWAP(a[left], a[mid], tmp);

        i = left + 1, j = right;
        while (true) {
            while (a[i].key <= a[left].key && i < right)
                i++;
            while (a[j].key > a[left].key)  // <= 가 맞으나 그러면 j > left도 추가 검사해야 하므로 더 비효율적
                j--;
            if (i < j)
                SWAP(a[i], a[j], tmp);
            else
                break;
        }
        SWAP(a[left], a[j], tmp);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

/* main */

#define DATASZ 16
int main()
{
    Element data[DATASZ];
    setData(data, DATASZ, 1, 26, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);
    
    quickSort(data, 0, DATASZ - 1);

    printData(data, DATASZ);
    return 0;
}
