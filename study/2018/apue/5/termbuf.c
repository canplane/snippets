/*
#include <unistd.h>
#include <stdio.h>
#define BUFSIZE 3

char buf[BUFSIZE];

int main(void)
{
    int n;

    if ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            perror("write error");
    if (ferror(stdin))
        perror("read error");

    return 0;
}
*/
#include <stdio.h>
#define BUFSIZE 3

char buf[BUFSIZE];

int main(void)
{
    int n;

    if (fgets(buf, BUFSIZE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF)
            perror("write error");
    if (ferror(stdin))
        perror("read error");

    return 0;
}

