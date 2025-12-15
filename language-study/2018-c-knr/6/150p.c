/* bit-field practice */
#include <stdio.h>

struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
} p;

int main(void)
{
    p.is_keyword = 1;
    printf("flags(%16llx) : %lu\n", &p, sizeof(p));
    printf("flags.is_keyword : %d\n", p.is_keyword);    // bit-field는 주소를 가질 수 없다. 구현 의존적. 

    return 0;
}