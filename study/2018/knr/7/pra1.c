#include <stdio.h>

int main(void)
{
    char s[2];

    printf("%p %p\n", &s[0], &s[1]);
    return 0;
}