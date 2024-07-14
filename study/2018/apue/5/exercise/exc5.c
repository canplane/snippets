#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

void err_quit(const char *, ...);

char buf[BUFSIZ];

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int fd2;

    if (argc != 3)
        err_quit("Usage : ./a.out <frompath> <topath>");
    if ((fp1 = fopen(argv[1], "r")) == NULL || (fp2 = fopen(argv[2], "w")) == NULL)
        err_quit("Open error");
    fd2 = fileno(fp2);

    if (fgets(buf, BUFSIZ, fp1) != NULL) {
        if (fputs(buf, fp2) < 0)
            err_quit("Write error");
        fsync(fd2);
    }
    if (ferror(stdin))
        err_quit("Read error");

    exit(0);
}

void err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    if (errno)
    {   fprintf(stderr, ": ");
        perror(NULL);
    }
    else
        fprintf(stderr, "\n");
    exit(errno);
}