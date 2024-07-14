/* readlink practice */

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#define BUFSIZE     4096

char buf[BUFSIZE];
struct stat stbuf;

int err_quit(const char *, ...);
int err_sys(const char *);

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2)
        err_quit("Usage : %s <sympath>", argv[0]);
    if (lstat(argv[1], &stbuf) < 0)
        err_sys("lstat error");
    if ((n = readlink(argv[1], buf, stbuf.st_size)) > 0)
    {
        if (write(0, buf, n) != n)
            err_sys("write error");
        printf("\n");
    }
    if (n < 0)
        err_sys("readlink error");
    return 0;
}

int err_quit(const char *msg, ...)
{
    va_list arg;
    va_start(arg, msg);

    vprintf(msg, arg);
    printf("\n");
    exit(2);
}

int err_sys(const char *msg)
{
    perror(msg);
    exit(1);
}