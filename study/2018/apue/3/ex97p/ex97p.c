#include "apue.h"
#include <fcntl.h>

char    buf1[] = "abcdefghij";
char    buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    int     fd;

    // in apue.h, #define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    /* 이제 오프셋은 10. */
    
    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    /* 이제 오프셋은 16384 */
    
    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    /* 이제 오프셋은 16394 */

    exit(0);
}

