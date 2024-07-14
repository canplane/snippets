/* pointer operation pratice */

#include <stdio.h>
#define ROW 10
#define COL 100
#define p   (arr + 1)

/*
    (* arr)[x]      == arr[0][x]
    * arr[x]        == arr[x][0]

    arr             == & arr[0]     -->     * arr   == arr[0]
    arr + n         == & arr[n]
    arr[n] + x      == & arr[n][x]
    
    (arr + n)[x]    == arr[n + x]
*/

int arr[ROW][COL];

int main(void)
{
    int i, j;
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            arr[i][j] = COL*i + j;
    
    printf("%d\n", (*arr)[3]);          // (row, col) == (0, 3)
    printf("%d\n", *arr[3]);            // (row, col) == (3, 0)

    printf("%d\n", (*p)[3] );           // (row, col) == (1, 3)
    printf("%d\n", *p[3] );             // (row, col) == (3+1, 0)

    printf("%d\n", *(arr[3]+1));        // (row, col) == (3, 1)
    printf("%d\n", * (& arr[2])[3]);    // (row, col) == (2+3, 0)

/*
    p               == arr + 1          == & arr[1]
    (*p)[3]         == (* (arr + 1))[3] == (* & arr[1])[3]  == (arr[1])[3]  == arr[1][3]
    *p[3]           == * (arr + 1)[3]   == * arr[1 + 3]     == * arr[4]     == arr[4][0]
    *(arr[3]+1)     == * (& arr[3][1])  == arr[3][1]
    *(& arr[2])[3]  == * (arr + 2)[3]   == * arr[2 + 3]     == * arr[5]     == arr[5][0]
*/

    return 0;
}
