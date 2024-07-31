#include <stdio.h>

typedef enum _enum { A = 1, B, C, D, E = 2 } ENUMM;     // _enum : enumeration tag, ENUMM : defined type
enum { A1, B1, C1 } v3;                                 // v3 : variable

int main()
{
    enum _enum v1;
    ENUMM v2;
    printf("%d\n", v1 = A);
    printf("%d\n", v1 = B);
    printf("%d\n", v1 = C);
    printf("%d\n", v1 = D);
    printf("%d\n", v1 = E);
    
    printf("%d\n", v2 = A);
    printf("%d\n", v2 = B);
    printf("%d\n", v2 = C);
    printf("%d\n", v2 = D);
    printf("%d\n", v2 = E);

    printf("%d\n", v3 = A);
    printf("%d\n", v3 = B);
    printf("%d\n", v3 = C);
    printf("%d\n", v3 = D);
    printf("%d\n", v3 = E);
    return 0;
}