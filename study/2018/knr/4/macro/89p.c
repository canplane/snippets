/* macro practice */

#include <stdio.h>

#define max(A, B)           ((A) > (B) ? (A) : (B))
#define dprint(expr)        printf(#expr " = %g\n", expr)   // # operator
#define paste(front, back)  front ## back                   // ## operator

int main(void)
{
    printf("%d\n", max(2, 3));
    printf("max(A, B)\n");

    int x = 5;
    double y = 4.0;
    dprint(x/y);
    dprint(5.0/4);
    printf("123" "456\n");
    
    int name1 = 3;
    printf("%d\n", paste(name, 1));

    return 0;
}
