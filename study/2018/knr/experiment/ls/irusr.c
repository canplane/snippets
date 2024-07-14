#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    printf("%o\n", S_IRUSR);
    printf("%o\n", S_IXOTH);
    return 0;
}