#include <stdio.h>

int test(int *b[100]);

int main(void)
{
    int a[10][100];

    int i, j;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 20; j++)
            a[i][j] = 100*i + j;         // 번지 순으로 오름차순 값 분배
    
    printf("%d\n", a[3][4]);
    printf("%d\n", test(a));
    
    return 0;
}

int test(int *b[100])
{
    return b[3][2];
}