#include <stdio.h>

int main(void)
{
    char amessage[] = "now is the time";    /* an array */
    char *pmessage = "now is the time";     /* a pointer */
    char a[2];
    //*(pmessage + 1) = 'k';                  /* BUS ERROR */

    printf("%d\n", *(a+2));
    return 0;
}
