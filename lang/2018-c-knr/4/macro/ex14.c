/* macro practice */

#include <stdio.h>
#define SWAP(T, X, Y)     \
    int temp = X;       \
    Y = X;              \
    X = temp;           \
    temp = 1

#if !defined(SWAP)
    #define LOGIC   1
#endif

#ifndef LOGIC
    #define LOGIC   2
#endif

#define print3(X, Y, Z)  printf(#X " = %d, " #Y " = %d, " #Z " = %d\n", X, Y, Z)
    

int main(void)
{
    int a = 5, b = 4;
    SWAP(int, a, b);
    print3(a, b, temp);
    printf("LOGIC == %d\n", LOGIC);

    return 0;
}