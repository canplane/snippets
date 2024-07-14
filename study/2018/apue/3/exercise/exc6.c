#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MODE    (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int
main(void)
{
    int fd, n;
    char buf[20];
    const char msg[10]  = "0123456789";
    const char c        = 'A';

    fd = open("input", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, MODE);
    write(fd, msg, 10);

    if (lseek(fd, 5LL, SEEK_SET) != 5LL)
        perror("lseek error");
    printf("%lld\n", lseek(fd, 0L, SEEK_CUR));
    // O_APPEND 플래그를 적용해도 오프셋 자체는 바꿀 수 있다. (5)

    if (write(fd, &c, 1) != 1)
        perror("write error");
    printf("%lld\n", lseek(fd, 0L, SEEK_CUR));
    // O_APPEND 플래그로 인해 write 연산이 수행되기 직전마다 오프셋이 현재 파일 크기로 갱신된다. (11)

    if (pwrite(fd, &c, 1, 3LL) != 1)
        perror("pwrite error");
    printf("%lld\n", lseek(fd, 0L, SEEK_CUR));
    // pwrite니까 오프셋은 갱신되지 않았다. 이전과 같다. (11)
    
    if (pwrite(fd, &c, 1, 11LL) != 1)
        perror("pwrite error");
    printf("%lld\n", lseek(fd, 0L, SEEK_CUR));
    // 마찬가지로 pwrite니까 파일 크기가 확장되었음에도 오프셋은 갱신되지 않았다. (11)
    
    if ((n = pread(fd, buf, 20, 0L)) > 0)
        write(STDOUT_FILENO, buf, n);
    write(STDOUT_FILENO, "\n", 1);

    close(fd);
    return 0;
}