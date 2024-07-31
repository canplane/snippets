/* puts/fputs가 출력하는 문자열 차이를 알아보기 위한 파이프라인 (pipe1 | pipe2) */

#include <stdio.h>

unsigned int arrlen(char *s);

int main(void)
{
    char oline[] = "abcdef";

    //fprintf(stderr, "\nputs(\"abcdef\") : ('\\n' is 10, '\\0' is 0)\n");
    //puts(oline);

    fprintf(stderr, "\nfputs(\"abcdef\", stdout) : ('\\n' is 10, '\\0' is 0)\n");
    fputs(oline, stdout);
    
    return 0;
}
