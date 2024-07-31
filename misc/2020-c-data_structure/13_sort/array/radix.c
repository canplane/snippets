/* radix sort (LSD, least significant digit)
 * 20200207
 * 링크드 리스트로 잇고, 기수(radix, base)를 사이즈로 하여 front, back 배열을 만든다. 가중치(weight)가 갱신될 때마다 링크드리스트를 따라 자릿값(digit)을 찾아 front, back을 갱신한 후 front, back을 링크로 이어 링크드리스트를 수정한다.
 * link[]를 매개변수로 받고 head 인덱스 반환, link의 마지막은 -1로 둔다.
 * 구현 시 link[]에 대한 임시 변수는 cur(current), radix 큐에 대한 임시 변수는 dgt(digit)으로 둘 것
 * O(d * n) (d는 가장 큰 데이터의 자릿수(승수 + 1) : log_r(k) + 1 (k는 최댓값, r은 기수))
 * not comparison sort, stable sort, not in-place sort
 * counting sort와 마찬가지로 음수 정수는 따로 정렬해야 하고, 부동 소수점 데이터의 경우 적용할 수 없음
 * 데이터 길이가 동일해야 사용 가능
 * MSD sort는 끝까지 가지 않을 수 있다는 장점이 있으나, 중간 과정마다 정렬을 확인해줘야 하므로 성능 차이가 없다. 구현의 편의성을 위해 LSD sort를 기준으로 한다.
 */

#include <stdio.h>
#include "data.h"
#include "link/double.c"
#include "link/single.c"

#define MAX2(x, y) ((x) > (y) ? (x) : (y))

int radixSort(Element a[], int link[], int size, int rdx)
{
    int head, tail, cur;
    int front[rdx], back[rdx], dgt;
    int maxnum, weight;

    head = 0;
    maxnum = a[0].key;
    for (cur = 0; cur < size; cur++) {
        link[cur] = cur + 1;
        maxnum = MAX2(a[cur].key, maxnum);
    }
    link[size - 1] = -1;
    
    for (weight = 1; weight <= maxnum; weight *= rdx) {
        for (dgt = 0; dgt < rdx; dgt++)
            front[dgt] = -1;
        
        for (cur = head; cur != -1; cur = link[cur]) {
            dgt = a[cur].key / weight % rdx;
            if (front[dgt] == -1)
                front[dgt] = cur;
            else
                link[back[dgt]] = cur;
            back[dgt] = cur;
        }

        for (dgt = 0; front[dgt] == -1; dgt++);
        head = front[dgt], tail = back[dgt];
        while (++dgt < rdx)
            if (front[dgt] != -1)
                link[tail] = front[dgt], tail = back[dgt];
        link[tail] = -1;
    }

    return head;
}

/* main */

#define RDX 4
#define DATASZ 16
int main()
{
    Element data[DATASZ];
    int link[DATASZ], head;
    setData(data, DATASZ, 1, 26, 5, 37, 1, 61, 26, 11, 59, 59, 15, 48, 26, 5, 19, 11);
    
    head = radixSort(data, link, DATASZ, RDX);
    doubleListSort(data, link, DATASZ, head);

    printData(data, DATASZ);
    return 0;
}