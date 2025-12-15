/* pointer practice */

#include <stdio.h>

int main(void)
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char b[10] = "abc def g";
    int *p = a;
    char *q = b;    // int로 두어버리면 q -> 'a', q+1 -> 'd', q+2 -> 'g'로 4씩 올라간다.
    int i;

    for (i = 0; i < 10; i++)
        printf("%llx\n", &a[i]);
    printf("\n");
    for (i = 0; i < 10; i++)
        printf("%llx\n", &b[i]);
    printf("\n");
    
    for (i = 0; i < 10; i++)
        printf("%llx -> \"%d\"\n", p+i, *(p+i));
    printf("\n");
    for (i = 0; i < 10; i++)
        printf("%llx -> \"%c\"\n", q+i, *(q+i));

    return 0;
}