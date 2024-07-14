/* how to truncate part of no integer while casting */

#include <stdio.h>

int main(void)
{
    double f = 1.9;
    double g = -1.9;

    printf("%d %d\n", (int) f, (int) g);
    return 0;
}