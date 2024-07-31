#include <stdio.h>
#include <string.h>

int main(void)
{
    char *str = "abcdef";
    int n;
    
    //str = "abcdef";

    printf("%s [%d]\n", str, n = (signed int)strlen(str));
    for (int i = 0; i <= n; i++)
        printf("%d : %x\n", str[i], &str[i]);
    return 0;
}