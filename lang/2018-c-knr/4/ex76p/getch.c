#include <stdio.h>
#define BUFSIZE     100

static char buf[BUFSIZE];      /* buffer for ungetch */
static int bufp = 0;           /* next free position in buf */

int _getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void _ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many character\n");
    else
        buf[bufp++] = c;
}