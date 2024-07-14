#include <stdio.h>
#define MAXLINE 1000

getstr();
void reverse();
void print();

main()
{
    int len;
    char org[MAXLINE];
    char rev[MAXLINE];

    len = getstr(org);
    reverse(org, rev, len);
    print(rev, len);
}

int getstr(char str[])
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        str[i] = c;
    str[++i] = '\0';
    return i;
}

void reverse(char org[], char rev[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        rev[i] = org[(len-1) - i];
}

void print(char str[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        putchar(str[i]);
    putchar('\n');
}