#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("uid : %u\ngid : %u\n", getuid(), getgid());

    return 0;
}