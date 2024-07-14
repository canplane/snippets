#include <stdio.h>

void print_arr(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* Insertion sort : n + 1 size */
void insertionSort(int a[], int n)
{
    int i, j;
    for (i = 2; i <= n; i++) {
        a[0] = a[i];
        for (j = i - 1; a[0] < a[j]; j--)
            a[j + 1] = a[j];
        a[j + 1] = a[0];
    }
}

/* Bubble sort */
void bubbleSort(int a[], int n)
{
    int i, j;
    int tmp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i;j++)
            if (a[j] > a[j + 1])
                tmp = a[j + 1], a[j + 1] = a[j], a[j] = tmp;
    }
}

/* Selection sort */
void selectionSort(int a[], int n)
{
    int i, j, min;
    int tmp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (a[min] > a[j])
                min = j;
        tmp = a[i], a[i] = a[min], a[min] = tmp;
    }
}

int main()
{
    int arr[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    selectionSort(arr, 10);
    print_arr(arr, 10);
}