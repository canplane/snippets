#include <ctype.h>
#include <stdio.h>
#include "calc.h"

/* getop:   get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = _getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = _getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = _getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        _ungetch(c);
    return NUMBER;
}
