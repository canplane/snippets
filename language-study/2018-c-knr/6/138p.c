#include <stdio.h>

struct {
    char c;
    int i;
} st;

int main(void)
{
    printf("%lu\n", sizeof(st));    /* sizes of the structure are 8 bytes, not 4. */
}