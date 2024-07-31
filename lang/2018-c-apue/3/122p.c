/* Are file descriptors seperated to process table?
if they are, why all they exist in same directory "/dev/fd"? */ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define OFLAG   (O_RDWR | O_CREAT | O_TRUNC)
#define MODE    (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(void)
{
    pid_t pid;
    int status;

    printf("before spawning : %d\n", open("a", OFLAG, MODE));
    
    switch(pid = fork())
    {
    case 0:
        printf("from child : %d\n", open("c", OFLAG, MODE));
        sleep(3);
        return 127;
        break;
    default:
        printf("from parent : %d\n", open("b", OFLAG, MODE));
        pid = waitpid(pid, &status, 0);
        printf("pid : %d, closed status : %d\n", pid, status);
        break;
    }
    return 0;
}