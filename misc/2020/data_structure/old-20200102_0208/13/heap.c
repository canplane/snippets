#include <stdio.h>

void printArray(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* // recursive function
void heapify(int a[], int root, int n)  // adjust
{
    int largest = root, left_child = 2 * root + 1, right_child = 2 * root + 2;
    int tmp;
    if (left_child < n && a[left_child] > a[largest])
        largest = left_child;
    if (right_child < n && a[right_child] > a[largest])
        largest = right_child;
    if (largest != root) {
        tmp = a[root], a[root] = a[largest], a[largest] = tmp;
        heapify(a, largest, n);
    }
}
*/

void heapify(int a[], int root, int n)  // adjust
{
    int left_child, right_child, largest;
    int tmp;
    while (1) {
        left_child = 2 * root + 1, right_child = 2 * root + 2;
        largest = root;
        if (left_child < n && a[left_child] > a[largest])
            largest = left_child;
        if (right_child < n && a[right_child] > a[largest])
            largest = right_child;
        if (largest == root)
            break;
        tmp = a[root], a[root] = a[largest], a[largest] = tmp;
        root = largest;
    }
}

void heapSort(int a[], int n)
{
    int i;
    int tmp;
    for (i = n/2; i >= 0; i--)
        heapify(a, i, n);
    for (i = n - 1; i > 0; i--) {
        tmp = a[0], a[0] = a[i], a[i] = tmp;
        heapify(a, 0, i);
    }
}

int main()
{
    int arr[] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    heapSort(arr, 10);
    printArray(arr, 10);
}
