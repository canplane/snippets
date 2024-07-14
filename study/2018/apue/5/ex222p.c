/* Linux는 출력 결과가 예상과 같지만, macOS는 다르게 나온다. */ 

#include "apue.h"

#define BSZ 48

int
main()
{
    FILE *fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    /*   a  a  a  a  ... \0  X  */
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
    /*  \0  a  a  a  ... \0  X  */
        err_sys("fmemopen failed");
    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf);
    fflush(fp);
    /*  offset이 0이었다
         h  e  l  l  o  ,     w
         o  r  l  d \0  a  a  a
         ...
         a  a  a  a  a  a \0  X
    */
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    /*   b  b  b  b  ... \0  X  */
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    /*  바로 전 offset이 12(\0인 곳)이었고 fseek에 의해 방출됨
         b  b  b  b  b  b  b  b
         b  b  b  b  h  e  l  l
         o  ,     w  o  r  l  d
        \0  b  b  b  b  b  b  b
         ...
         a  a  a  a  a  a \0  X
    */
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    /*   c  c  c  c  ... \0  X  */
    fprintf(fp, "hello, world");
    fclose(fp);
    /*  fclose에 의해 방출됨 (이 때까지 기록된 스트림 길이 중 max인 상황에만 오프셋에 \0 기록)
         h  e  l  l  o  ,     w
         o  r  l  d  c  c  c  c
         ...
         c  c  c  c  c  c \0  X
    */
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    return(0);
}