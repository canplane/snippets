#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MAXLINE 4096

char buf[MAXLINE];
int err_do(char *);

int main(int argc, char *argv[])
{
    while (fgets(buf, MAXLINE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF)
            err_do(*argv);
    if (ferror(stdin))
        err_do(*argv);
    return 0;
}

int err_do(char *msg)
{
    perror(msg);
    exit(errno);
}