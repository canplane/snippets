#include <stdio.h>
#define EOFSIGN "^C"

int main(int argc, char *argv[])
{
    FILE *fp;
    int c, i;

    if (argc < 2)
    {
        while ((c = getchar()) != EOF)
            putchar(c);
        if (c == EOF)
            printf("%s\n", EOFSIGN);    // 굳이 이렇게 표시 안해도 알아서 ^C 표시해주는거 같더라
        return 0;
    }

    for (i = 1; i < argc; i++)
    {
        if ((fp = fopen(argv[i], "r")) == NULL)
            break;
        printf("%p\n", fp);
        while ((c = getc(fp)) != EOF)
            putc(c, stdout);
    }
    if (i == argc)
        return 0;
    printf("%s: %s: No such file or directory\n", argv[0], argv[i]);
    return -1;
}
// fclose를 안 넣었넹