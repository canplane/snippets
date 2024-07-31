#include <stdio.h>
#include <string.h>

int main(void)
{
    char v[2][5] = {"abcf", "abcd"};
    printf("%d\n", strcmp(v[0], v[1]));
    return 0;
}