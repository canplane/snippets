#include <stdio.h>
#include <unistd.h>

int main(void)
{
    /*
    if (setvbuf(stdout, NULL, _IONBF, 0))
        perror("setbuf error");
    */
    
    /*
    a, b, c, d, e가 순차적으로 1초씩 출력되어야 하는데 기본값이 줄 단위 버퍼링이라 될 리가 없다.
    프로세스가 종료될 때서야 abcde가 한꺼번에 나온다.
    setvbuf를 통해 버퍼링 없음으로 지정하거나, fflush를 이용하면 의도대로 출력된다.
    */
    for (int i = 0; i < 5; i++)
    {
        putchar('a' + i);
        if (i == 2)
            putchar('\n');
        // 줄 단위 버퍼링으로 개행 문자가 나오거나 꽉 차면 버퍼가 방출되므로 abc가 출력된다.
        
        /* fflush(stdout); */
        sleep(1);
    }
    sleep(10);
    return 0;
}