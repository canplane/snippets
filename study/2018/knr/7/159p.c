/* scanf buffer problem */

#include <stdio.h>

void scan1(char *A, char *B)
{
    scanf("%c%c", A, B);
    // %c 사이에 '\n\n'를 넣어도 둘 다 white-space 문자이므로 개행 한번만 해도 무시된다. ' ', '\t'를 이용해도 된다.
}

void scan2(char *A, char *B)
{
    scanf("%c\n", A);
    printf("[]\n");
    scanf("%c", B);
    // 맨 처음과 맨 끝의 conversion specification(%) 사이에 있지 않은 white-space 문자들은 무시된다.
    // 띄엄띄엄 떨어지는것과 상관없이 각 scanf의 문자열들을 합할 수 있다 -> "%c\n" "%c\n" == "%c\n%c\n"
}

void scan3(int *A, int *B)
{
    scanf("%d %d", A, B);
    // 이때 버퍼 '\n'가 남아있지만 %d 형식이 아니므로 다시 scanf를 읽을 때 사라진다.
    //%c는 '\n'도 포함할 수 있으므로 문제가 발생할 수 있다.
    scanf("%d %d", A, B);
}

int main(void)
{
    char c1, c2;
    int i1, i2;
    
    scan2(&c1, &c2);

    printf("A == %d, B == %d\n", c1, c2);
    while (1)
        printf("%d ", getchar());
    return 0;
}