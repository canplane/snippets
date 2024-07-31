#include <stdio.h>

int main(void)
{
    char *p = NULL;
    scanf("%ms", &p);
    printf("%p", p);
}