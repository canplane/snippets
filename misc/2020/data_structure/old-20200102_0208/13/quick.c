#include <stdio.h>

void printArray(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void quickSort(int a[], int left, int right)
{
    int i, j;
    int tmp;
    if (left < right) {
        i = left, j = right;
        while (i < j) {
            while (a[i] <= a[left] && i < right)
                i++;
            while (a[j] > a[left])
                j--;
            if (i < j)
                tmp = a[j], a[j] = a[i], a[i] = tmp;
        }
        tmp = a[j], a[j] = a[left], a[left] = tmp;
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

void mid_quickSort(int a[], int left, int right)
{
    // pivot : left
    int mid, i, j;
    int tmp;
    if (left < right) {
        mid = (left + right)/2, tmp = a[left], a[left] = a[mid], a[mid] = tmp;
        i = left, j = right;
        while (i < j) {
            while (a[i] <= a[left] && i < right)
                i++;
            while (a[j] > a[left])
                j--;
            if (i < j)
                tmp = a[j], a[j] = a[i], a[i] = tmp;
        }
        tmp = a[j], a[j] = a[left], a[left] = tmp;
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main()
{
    int arr[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    quickSort(arr, 0, 9);
    printArray(arr, 10);
}
