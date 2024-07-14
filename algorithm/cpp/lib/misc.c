/* MSB가 1일 때(음수) >> 연산은 CPU에 따라 음수 유지를 할 수 있다. (내 맥은 음수 유지)
 * 최댓값 구할 때는 (0xFFFFFFFF >> 1) + 1 하거나
 * 혹은 아래의 함수를 쓴다.
 */
{
    int x;
    for (x = 0x1; x; x <<= 1) {
        printf("%X (%d)\n", x, x);
    }

    int y = 0xFFFFFFFF >> 1;    // 최댓값
    printf("%X + 1 = %X (%d + 1 = %d)\n", y, y + 1, y, y + 1);  // 최솟값

    int z = 0;
    memset(&z, -1, sizeof(int));
    printf("z = %X\n", z);  // 0xFFFFFFFF
    printf("z = %X\n", z >> 1); // 0xFFFFFFFF
}


// 리틀 엔디언 기준
void minval(void *p, size_t len)
{
    int i;
    for (i = 0; i < len; i++)
        ((char *)p)[i] = 0x0;
    ((char *)p)[len - 1] = 0x80;    // 빅 엔디언이면 ((char *)p)[0]
}

void maxval(void *p, size_t len)
{
    int i;
    for (i = 0; i < len; i++)
        ((char *)p)[i] = 0xFF;
    ((char *)p)[len - 1] = 0x7F;    // 빅 엔디언이면 ((char *)p)[0]
}
