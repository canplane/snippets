#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int fd = 1;
    const char buf[] = "hello world!\n";
    if (dup2(fd, 0) < 0)
        perror("0");
    if (dup2(fd, 1) < 0)
        perror("1");
    if (dup2(fd, 2) < 0)
        perror("2");
    write(0, buf, strlen(buf));
    return 0;
}
// 파일 서술자 0, 1, 2도 닫힌다! 그럼 다시 어떻게 열지..?