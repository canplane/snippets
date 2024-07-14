#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define BUFSIZE 1000
#define NUMBER  0

static int stack[BUFSIZE];
static int len = 0;
char *errcode[] = {
    "ERROR : INVALID SYNTAX. IF YOU TYPED OUT * TO MULTIPLY, REPLACE * WITH \"*\"",
    "ERROR : STACK OVERFLOW",
    "ERROR : DIVIDER VALUE IS ZERO"
};

int atoi(char *);
void push(int);
int pop(void);

int main(int argc, char *argv[])
{
    int temp, i = 0;
    char c;
    
    while (++i < argc)
    {
        //printf("%d %c\n", len, argv[i][0]);
        if (!isdigit(c = argv[i][0]) && strlen(argv[i]) == 1)
        {
            switch(c)
            {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                temp = pop();
                push(pop() - temp);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                if ((temp = pop()))
                    push(pop() / temp);
                else
                {
                    printf("%s\n", errcode[2]);
                    return -1;
                }
                break;
            default:
                printf("%s\n", errcode[0]);
                return -1;
            }
        }
        else
        {
            if (atoi(argv[i]))
            {
                printf("%s\n", errcode[0]);
                return -1;
            }
        }
    }
    
    if (len != 1)
    {
        printf("%s\n", errcode[0]);
        return -1;
    }
    else
    {
        printf("ANSWER : %d\n", stack[0]);
        return 0;
    }
}

int atoi(char *str)
{
    int n, sign = 1;
    char c;
    
    if (isdigit(c = *str))
        n = c - '0';
    else if (c == '-')
        sign = -1;
    else
        return -1;

    while ((c = *++str) != '\0')
    {
        if (isdigit(c))
            n = 10*n + (c - '0');
        else
            return -1;
    }
    push(sign * n);
    return NUMBER;
}

void push(int n)
{
    if (len < BUFSIZE - 1)
        stack[len++] = n;
    else
        printf("%s\n", errcode[1]);
}

int pop(void)
{
    if (len > 0)
        return stack[--len];
    else
    {
        printf("%s\n", errcode[0]);
        return -1;
    }
}