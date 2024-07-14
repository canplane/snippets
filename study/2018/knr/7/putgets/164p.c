/*
    int fputs(char *line, FILE *fp);
    char *fgets(char *line, int maxline, FILE *fp);
    int puts(char *line);                               return 0 or EOF(error)
    char *gets(char *line);                return line or NULL(error or EOF)
*/

#include <stdio.h>
#define MAXLINE 100

unsigned int arrlen(char *s);

int main(void)
{
    char oline[] = "abcdef";
    char iline[10];
    int len;

    puts(oline);
    gets(iline);
    //fputs(oline, stdout);
    //fgets(iline, MAXLINE, stdin);

    printf("indices of iline : %u\n", arrlen(iline));

    while (1)   // 버퍼 남아있는지 확인. gets/fgets 모두 버퍼는 비워짐(개행 문자 안 남아있음)
        printf("%d ", getc(stdin));
    return 0;
}

unsigned int arrlen(char *s)   // including '\0'
{
    unsigned int i = 1;
    while (*s++)
    {
        printf("%d ", *s);
        i++;
    }
    printf("\n");
    return i;
}