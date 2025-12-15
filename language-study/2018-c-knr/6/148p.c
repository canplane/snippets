/* structure versus union */
#include <stdio.h>

typedef struct {
    char c;
    short s;
    int i;
} STRUCT;

typedef union {
    char c;
    short s;
    int i;
} UNION;

int main(void)
{
    printf("%lu, %lu\n", sizeof(STRUCT), sizeof(UNION));
    return 0;
}