#include <stdio.h>

void _print(int v[], int n);
void shellsort(int v[], int n);

int main()
{
    int arr[9] = {11, 3, 7, 4, 5, 2, 9, 1, 8};
    int i, n = 9;

    _print(arr, n);
    shellsort(arr, n);
    _print(arr, n);

    return 0;
}

void _print(int v[], int n)
{
    int i;

    printf("{\t");
    for (i = 0; i < n; i++)
        printf("%2d%s\t", v[i], (i == n-1)? "": ",");
    printf("}\n");
}

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}