#include <stdio.h>
#include <unistd.h>

int main(void)
{
    /*
    const char str[] = "ab" "%d";
    char *p = (char * const)str;
    while (*p)
        printf("%d ", *p++);
    */
    int c, res;

    for (int i = 0; i < 5; i++)
    {
        putchar(i+'0');
        if ((c = getchar()) != '\n')
            while ((res = getchar()) != '\n' && res != EOF);
        printf("%c\n", c);
    }
    
}