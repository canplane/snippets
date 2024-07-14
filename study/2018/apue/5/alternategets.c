/*
static을 통해 gets 함수를 재정의하려 했으나 컴파일 단계에서 헤더와 모순이라며 오류가 출력된다.
근데 그냥 함수를 매크로로 덮어씌우면 되는거였다...
*/

#include <stdio.h>
#define BUFSIZE 512
/*
#ifdef  gets
    #undef  gets
    #define gets(buf, n) ( fgets(buf, n, stdin) )
#else
    static char *_gets(char *buf, int n) {
        return fgets(buf, n, stdin);
    }
    static char *(*gets)(char *, int) = &_gets;
#endif
*/
#define gets(buf, n) ( fgets(buf, n, stdin) )
 
char buf[BUFSIZE];

int main(void)
{
    gets(buf, BUFSIZE);
    puts(buf);

    return 0;
}

