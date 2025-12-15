/* gets defect test */

#include <stdio.h>
#define NUM 5
/* print the address of buf and its neighborhoods */
#define print()   {                                                     \
    for (p = buf; (unsigned int) (p - buf) <= sizeof(buf) + NUM; p++)   \
      printf("%p : '%c'(%x)\n", p, *p, *p);                             \
}

int put(void);
int get(void);
int fget(void);


int main(void)
{
    //put();
    //get();
    fget();
    return 0;
}

int put(void)
{
    char buf[3] = {'a', 'b', 'c'};
    char *p;
    FILE *fp;
    fp = fopen("w.file", "w+");

    print();
    /* write buf on file */
    fputs(buf, fp);

    return 0;
}

int get(void)
{
    char buf[3];
    char *p;
    FILE *fp;

    print();
    /* read file and save it to buf */
    gets(buf);
    print();

    return 0;
}
/* gets는 버퍼보다 큰 줄을 받아버리면 오버플로우해서 덮어씌움, size 인수가 없어서 통제도 못한다. -> unsafe */

int fget(void)
{
    char buf[3];
    char *p;
    FILE *fp;

    print();
    /* read file and save it to buf */
    fgets(buf, sizeof(buf) /*+ NUM*/, stdin);
    print();

    return 0;
}
/* fgets는 버퍼의 사이즈를 정확히 전달한다면 절단하지만 제대로 전달 안하면 역시 오버플로우해서 덮어씌움 */