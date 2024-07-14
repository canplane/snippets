#include <stdio.h>
#define MAXSZ 1000

void print_arr(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void merge(int dst[], int src[], int left, int mid, int right)
{
    int i, j, k;
    for (k = i = left, j = mid + 1; i <= mid && j <= right; )
        dst[k++] = src[i] < src[j] ? src[i++] : src[j++];
    while (i <= mid)
        dst[k++] = src[i++];
    while (j <= right)
        dst[k++] = src[j++];
}

void mergePass(int dst[], int src[], int n, int s)
{
    int i;
    for (i = 0; i + 2*s - 1 < n; i += 2*s)
        merge(dst, src, i, i + s - 1, i + 2*s - 1);
    if (i + s - 1 < n)
        merge(dst, src, i, i + s - 1, n - 1);
    else
        while (i < n) {
            dst[i] = src[i];
            i++;
        }
}

int extra[MAXSZ];
void mergeSort(int a[], int n)
{
    int s = 1;
    while (s < n) {
        mergePass(extra, a, n, s);
        s *= 2;
        mergePass(a, extra, n, s);
        s *= 2;
    }
}

int main()
{
    int arr[] = {61, 59, 48, 26, 37, 19, 15, 11, 5, 1};
    mergeSort(arr, 10);
    print_arr(arr, 10);
}