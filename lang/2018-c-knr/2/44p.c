#include <stdio.h>

int main()
{
    printf("%d\n", -1L < 1U);       // 1U convert to 1L : true
    printf("%d\n", -1L < 1UL);      // -1L covert to -1UL : false
    printf("%d\n", -1 < 1U);        // false

    printf("%u\n", -1);             // power(2, 64) - 1
    printf("%lu\n", sizeof(int));   // int type in 64 bytes system is 4 bytes

    return 0;
}