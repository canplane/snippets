/* 터미널 read할 때 반환값이 0(파일 끝)인 상황이 나오지 않으므로 루프를 빠져나오게 하는 방법 */

#include <unistd.h>
#define MAXLINE 5

char buf[MAXLINE];

int main(void)
{
    int n;

    do
    {
        n = read(STDIN_FILENO, buf, MAXLINE);
        write(STDOUT_FILENO, buf, n);
    } while (n == MAXLINE && buf[n-1] != '\n');

    return 0;
}

/*
최대 MAXLINE만큼 받을 때 read의 반환값이 MAXLINE와 똑같다면
(a) 뒤에도 문자열이 이어지거나, (b) 뒤에 문자열이 이어지지 않는 경우가 있다.
(b)의 경우는 또 read를 호출하면 0이 나오지 않고 명령줄에서 또 입력을 받게 되므로 이를 방지해야 한다.
따로 변수 m을 정의하고 read를 통해 받은 버퍼의 데이터 맨 끝이 '\n'인지 아닌지 대조한다.
터미널은 한 줄을 기준으로 입력되므로 만약 맞다면 입력의 끝이므로 루프를 빠져 나와야 한다.
*/

/*
+ getchar에 대해서는 아래와 같이 적용할 수 있겠다.

int c, res;
if ((c = getchar()) != '\n')
    while ((res = getchar()) != '\n' && res != EOF);
*/