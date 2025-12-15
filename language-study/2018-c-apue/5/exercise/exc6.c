/* ./a.out 2> file와 같이 오프셋 테스트 */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *msg = "Hello", c;

    fprintf(stderr, "%lld\n%lld\n\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR), lseek(STDIN_FILENO, 0L, SEEK_CUR));

    while (*msg)
        putchar(*msg++);
    sleep(3);
    fprintf(stderr, "%lld\n%lld\n\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR), lseek(STDIN_FILENO, 0L, SEEK_CUR));

    if ((c = getchar()) != '\n')
    {
        fprintf(stderr, "%lld\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR));
        while (getchar() != '\n')
            fprintf(stderr, "%lld\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR));
    }
    fprintf(stderr, "\n\n\n%lld\n%lld\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR), lseek(STDIN_FILENO, 0L, SEEK_CUR));
    fflush(NULL);
    fprintf(stderr, "\n\n\n%lld\n%lld\n", lseek(STDOUT_FILENO, 0L, SEEK_CUR), lseek(STDIN_FILENO, 0L, SEEK_CUR));
}