#include <stdio.h>
#include <string.h>

int trim(char s[]);

int main()
{
    int n;
    char str[] = "abcd efg hi   ";
    n = trim(str);
    printf("%d, %s\n", n, str);
    printf("%lu, %lu, %lu, %lu, %lu, %lu, %lu\n", sizeof(short), sizeof(int), sizeof(long), sizeof(long long), \
    sizeof(float), sizeof(double), sizeof(long double));
    return 0;
}

int trim(char s[])
{
    int n;
    for (n = strlen(s)-1; n>=0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
    s[n+1] = '\0';
    return n;
}