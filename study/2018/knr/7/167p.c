#include <stdio.h>

int main(void)
{
    int i = 0x64636261;     // 0x61 == 97 == 'a'
    
    printf("%c %c %c %c\n", i, i, i, i);    // [a, ,a, ,a, ,a,\n] 출력, 뒤를 읽는다.
    return 0;
}