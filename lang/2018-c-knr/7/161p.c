#include <stdio.h>

int main(void)
{
    char c = 'a', d;
    putchar(c);
    putchar(d = getc(stdout));
    // stdout은 이미 "w" mode로 열려 있으므로 getc를 통해 "r" mode로 전환할 수 없다. 따라서 d = EOF가 된다. 
    printf("%d", d);

    return 0;
}