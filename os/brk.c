/* 
 * brk test
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2021-11-05
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    void *curr_brk;
    printf("initial program break: %p\n", curr_brk = sbrk(0x0));
    //printf("brk retval: %d\n", brk(curr_brk + 0x1000));
    //printf("current program break: %p\n", sbrk(0x0));
    malloc(0x1000);  // may occur error if previous brk
    printf("after malloc: %p\n", sbrk(0x1000));
    printf("increment: %p\n", sbrk(-0x1000));
    printf("decrement: %p\n", sbrk(0x0));
}
