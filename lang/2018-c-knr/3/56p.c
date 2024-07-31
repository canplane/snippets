#include <stdio.h>

int main()
{
    int n = -2, a = -1, b = 1, z = 0;

    if (n > 0)
        if (a > b)
            z = a;
        else
            z = b;

    printf("%d\n", z);
    return 0;
}