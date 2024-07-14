#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int             i, fd;
    struct stat     statbuf;
    struct timespec times[2];
    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &statbuf) < 0) {  /* 현재 시간들을 얻는다. */
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* 파일 절단 */
            err_ret("%s: open error", argv[i]);
            continue;
        }
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
#else
        times[0].tv_sec = statbuf.st_atime;
        times[0].tv_nsec = statbuf.st_atimensec;
        times[1].tv_sec = statbuf.st_mtime;
        times[0].tv_nsec = statbuf.st_mtimensec;
#endif
        if (futimens(fd, times) < 0)        /* 시간들을 재설정한다. */
            err_ret("%s: futimens error", argv[i]);
        close(fd);
    }
    exit(0);
}
