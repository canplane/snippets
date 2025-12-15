#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MAXLINE 4096

char buf[MAXLINE];
int n;
int err_do(char *);

int main(int argc, char *argv[])
{
    while ((n = read(STDIN_FILENO, buf, MAXLINE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
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