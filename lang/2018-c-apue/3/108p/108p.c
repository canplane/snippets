#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
    int     rd, wd, n, status;
    char    buf;
    pid_t   pid;

    rd = open("in", O_RDONLY, 0);

    switch (pid = fork())
    {
    case 0:
        wd = open("out_child", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        while ((n = read(rd, &buf, 1)) > 0)
            write(wd, &buf, n);
        
        close(wd);
        close(rd);
        exit(127);
        break;
    default:
        waitpid(pid, &status, 0);
        
        wd = open("out", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        while ((n = read(rd, &buf, 1)) > 0)
            write(wd, &buf, n);
        
        if (errno > 0)
            perror("");
        break;
    }
    return 0;
}