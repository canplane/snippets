#include <stdio.h>

int main(void)
{
    double f[] = {32, 16, 8, 4, 2, 1, 0.5, -0.25, 0.125, 0.0625};

    for (int i = 0; i < 10; i++)
        printf("%a\n", f[i]);
    return 0;
}