#include <stdio.h>

int test(int);

int main(void)
{
    printf("%d\n", test(1));
    printf("%d\n", test(0));
    printf("%d\n", test(0));
    printf("%d\n", test(0));
    printf("%d\n", test(0));
    return 0;
}

int test(int init)
{
    static int i = 0;   // static and extern can't initialize with variable but constant value.     static int i = init (X)

    if (init)
        i = 0;
    else
        i++;
    return i;
}
