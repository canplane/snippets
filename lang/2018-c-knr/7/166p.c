/* ungetc(int c, FILE *fp) practice */

#include <stdio.h>

int main(void)
{
    int c;
    c = getchar();
    ungetc(c, stdin);
    // 'a', '\n'를 차례대로 입력할 때 ungetc에 의해 다시 버퍼로 'a'가 들어간다고 볼 수 있다.
    
    while (1)
        printf("%d ", getchar());
    
    return 0;
}