#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int c, n;
int err_do(char *);

int main(int argc, char *argv[])
{
    while ((n = read(STDIN_FILENO, &c, 1)) > 0)
        if (write(STDOUT_FILENO, &c, n) != n)
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