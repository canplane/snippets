#include <stdio.h>
//#include <string.h>

int _strcmp(char *, char *);

int main(void)
{
    char *a = "abcd";
    char *b = "abcf";

    printf("%d\n", _strcmp(a, b));
    return 0;
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int _strcmp(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

/* a, b가 서로 같은 구문을 가지고 있지 않으면 크기 비교가 안됨 */