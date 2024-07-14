#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

main()
{
    
}

int _getline(char s[], int lim)
{
    int i, c;
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n')
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int calc(char s[])
{
    int i, j, k;
    for (i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]))
            continue;
        switch (s[i])
        {
        case '+':
            s[i] = (s[i-2] - '0') + (s[i-1] - '0') + '0';
        }
    }
     
}

int atoi(char s)
{
    
}