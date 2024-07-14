/* puts/fputs가 출력하는 문자열 차이를 알아보기 위한 파이프라인 (pipe1 | pipe2) */

#include <stdio.h>
#define MAXLINE 10

int main(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
        printf("%d ", c);
    printf("\n\n");
    return 0;
}
/*
getc(stdin) (== getchar())는 버퍼 다 받으면 pause 있는데
stdin이 아닌 다른 파일 스트림이면 EOF 반환한다.
*/
