/* 디렉터리는 open을 통해 열 수 있지만, read를 통해 읽으려 하면 -1 반환 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

#ifndef DIRSIZ
#define DIRSIZ      14
#endif
struct dirent                   /* directory entry */
{
    ino_t d_ino;                /* inode number */
    char d_name[DIRSIZ];        /* long name does not have '\0' */
};


DIR *opendir(char *);
Dirent *readdir(DIR *);

int main(int argc, char **argv)
{
    Dirent *dp;
    DIR *dfd;
    char *name = argv[1];

    if ((dfd = opendir(name)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", name);
        exit(1);
    }
    if ((dp = readdir(dfd)) == NULL) {
        fprintf(stderr, "dirwalk: can't read %s\n", name);
        exit(1);
    }
    exit(0);
}

DIR *opendir(char *dirname)
{
    int fd;
    struct stat stbuf;
    DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
     || fstat(fd, &stbuf) == -1
     || (stbuf.st_mode & S_IFMT) != S_IFDIR
     || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
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