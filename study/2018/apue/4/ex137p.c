#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");
    if (access(argv[1], W_OK) < 0)
        err_ret("access error for %s", argv[1]);
    else
        printf("write access OK\n");
    if (open(argv[1], O_WRONLY) < 0)
        err_ret("open error for %s", argv[1]);
    else
        printf("open for writing OK\n");
    exit(0);
}