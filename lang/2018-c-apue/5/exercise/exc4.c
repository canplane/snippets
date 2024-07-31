#include <stdio.h>
#include <unistd.h>

int
main(void)
{
    unsigned char    c;

    while (1)
    {
        c = getchar();
        fprintf(stderr, "%c[%u]\n", c, c);
        putchar(c);
        
        if (c == EOF)
            break;
        sleep(1);
    }
}