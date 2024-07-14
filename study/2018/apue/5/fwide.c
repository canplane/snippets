#include <stdio.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int ret;
    errno = 14;
    ret = fwide(stdin, 1);
    ret = fwide(stdin, -1);
    printf("%d\n", ret);
    perror(NULL);
    return 0;
}
/* 에러가 검출이 아예 안되는데? */