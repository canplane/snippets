/* 디렉터리는 open을 통해 열 수 있지만, read를 통해 읽으려 하면 -1 반환 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>      /* typedefs */
#define BUFSIZE 1000
#define NAME_MAX    14          /* longest filename component; */
                                /* system-depenent */

typedef struct {                /* portable directory entry: */
    long ino;                   /* inode number */
    char name[NAME_MAX+1];      /* name + '\0' terminator */
} Dirent;

typedef struct {                /* minimal DIR: no buffering, etc. */
    int fd;                     /* file descriptor for directory */
    Dirent d;                   /* the directory entry */
} DIR;

#ifndef DIRSIZ
#define DIRSIZ      14
#endif
#include <sys/stat.h>
struct dirent                   /* directory entry */
{
    ino_t d_ino;                /* inode number */
    char d_name[DIRSIZ];        /* long name does not have '\0' */
};


char buf[BUFSIZE];
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
    int fd, n;
    struct dirent dirbuf;

    if (argc != 2)
        error("2 arguments needed");
    else
    {
        if ((fd = open(argv[1], O_RDONLY, 0)) < 0)
            error("open error");        
        while (1)
        {
            if ((n = read(fd, (char *) &dirbuf, sizeof(dirbuf))) < 0)
                error("read error");
            else if (n == 0)
            {
                printf("[eof]\n");
                break;
            }
            
            if (write(1, buf, n) != n)
                error("write error");
        }
    }
    exit(0);
}

Dirent *readdir(DIR *dp)
{
    struct dirent dirbuf;   /* local directory structure */
    static Dirent d;        /* return: portable structure */

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
    {
        if (dirbuf.d_ino == 0)      /* slot not in use */
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';      /* ensure termination */
        return &d;
    }
    return NULL;
}

void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error : ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    exit(1);
}