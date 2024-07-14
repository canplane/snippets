#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

double atof(char s[]);
int _getstr(char s[]);

int main()
{
    char str[MAXLINE];

    _getstr(str);
    printf("%lf\n", atof(str));
    
    return 0;
}

double atof(char s[])
{
    double val = 0, power = (double)1/10;
    int i = 0, sign;

    sign = (s[i] == '-')? -1: 1;

    if (s[i] == '+' || s[i] == '-')
        i++;
    for (; isdigit(s[i]); i++)
        val = 10*val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (; isdigit(s[i]); power /= 10, i++)
        val += power*(s[i] - '0');
    
    return sign*val;
}

int _getstr(char s[])
{
    int i, c;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}