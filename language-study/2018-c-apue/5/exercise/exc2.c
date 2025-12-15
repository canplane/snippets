#include <stdio.h>
#include <unistd.h>     /* to use sleep(3) */

char buf[5];

int main(void)
{
    int t = 0;

    while (fgets(buf, 5, stdin) != NULL) {
        if (fputs(buf, stdout) < 0) {
            perror("stdout error");
            return 2;
        }
        printf("\n-------------------- %d second(s)\n", t++);
        sleep(1);
    }
    if (ferror(stdin))
    {
        perror("stdin error");
        return 1;
    }
    return 0;
}