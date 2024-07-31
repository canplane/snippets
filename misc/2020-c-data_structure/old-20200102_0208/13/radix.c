#include <stdio.h>
#define MAX2(x, y) ((x) > (y) ? (x) : (y))

void printLinkedArray(int a[], int link[], int idx)
{
    for (; idx != -1; idx = link[idx])
        printf("%d ", a[idx]);
    printf("\n");
}

/* LSD */
int radixSort(int a[], int link[], int n, int rdx)
{
    int first, last, idx;
    int front[rdx], rear[rdx], dgt;
    int max, pos;

    first = 0, max = a[0];
    for (idx = 0; idx < n; idx++) {
        link[idx] = idx + 1;
        max = MAX2(a[idx], max);
    }
    link[n - 1] = -1;
    
    for (pos = 1; pos <= max; pos *= rdx) {
        for (dgt = 0; dgt < rdx; dgt++)
            front[dgt] = -1;
        
        for (idx = first; idx != -1; idx = link[idx]) {
            dgt = (a[idx] / pos) % rdx;
            if (front[dgt] == -1)
                front[dgt] = idx;
            else
                link[rear[dgt]] = idx;
            rear[dgt] = idx;
        }

        for (dgt = 0; front[dgt] == -1; dgt++);
        first = front[dgt], last = rear[dgt];
        while (++dgt < rdx) {
            if (front[dgt] != -1)
                link[last] = front[dgt], last = rear[dgt];
        }
        link[last] = -1;
    }
    
    return first;
}

#define ARRSZ 10
#define RDX 10
int main()
{
    int arr[] = {179, 208, 306, 93, 859, 984, 55, 9, 271, 33};
    int link[ARRSZ], first;
    first = radixSort(arr, link, ARRSZ, RDX);
    printLinkedArray(arr, link, first);
    return 0;
}