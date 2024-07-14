#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int a;

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        a = 15;
        printf("child\n");
    }
    else if (pid > 0) {
        waitpid(pid, NULL, 0);
        printf("parent\n");
        printf("%d\n", a);
    }
}