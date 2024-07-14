#include <stdio.h>

int main(void)
{
    unsigned int    u;
    signed int      d = -1;

    printf("%u %d\n", d, d);

    u = (unsigned) d;
    printf("%u %d\n", u, d);
}