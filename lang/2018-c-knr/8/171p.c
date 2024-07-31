#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef  putchar
#undef  putchar
#endif

#ifdef  BUFSIZ
#undef  BUFSIZ
#define BUFSIZ  1000
#endif

int _getchar(void);
int putchar(int c);

int main(void)
{
    getchar();

    exit(0);
}

/* getchar: unbuffered single character input */ 
int _getchar(void)
{
    char c, asc;
    long i;
    
    do
    {
        i  = read(0, &c, 1);
        asc = (unsigned char)i + '0';
        write(1, &asc, 1);
    } while (--i > 0);
    
    return 0;
}

int putchar(int c)
{
    char d = (unsigned char) c;
    return (write(1, &d, 1) == 1) ? d : EOF;
}

/* getchar: simple buffed version */
/*
int getchar(void)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {   // buffer is empty
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
*/

