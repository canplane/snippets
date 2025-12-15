#include <stdio.h>
#define BUFSIZE 1024

char buf[BUFSIZE];

int main(void)
{
    /*
    // code to create dummy file
    char buf1[] = "abcd";
    char buf2[] = "ABCD";

    fputs(buf1, stdout);
    for (int i = 0; i < 2; i++)
        putc('\0', stdout);
    putc('\n', stdout);
    putc('\n', stdout);
    fputs(buf2, stdout);
    */
   int n = 0;
    while (fgets(buf, BUFSIZE, stdin) != NULL)
    {
        printf("line %d : ", ++n);
        for (int i = 0; i < BUFSIZE; i++)
        {
            putchar(buf[i]);
            buf[i] = '\0';
        }
    //    if (fputs(buf, stdout) == EOF)
    //        break;
    }

    return 0;
}
