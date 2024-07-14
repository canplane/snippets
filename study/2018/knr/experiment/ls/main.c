#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FLAG_LG     01
#define FLAG_SZ     02
#define PATH_LEN    1000

void listdir(char *, unsigned int);
static unsigned int getflag(char *);
static off_t fsize(char *);
static void error(char *, ...);

char *prog;

int main(int argc, char *argv[])
{
    unsigned int flag = 0;
    prog = *argv;

    if (argc == 1)
        listdir("./", flag);
    else
    {
        --argc, ++argv;
        if (argc == 1)
        {
            if ((flag = getflag(*argv)) != 0)
                listdir("./", flag);
            else
                listdir(*argv, flag);
        }
        else
        {
            if ((flag = getflag(*argv)) != 0)
                --argc, ++argv;
            for (; argc > 0; --argc, ++argv)
                listdir(*argv, flag);
        }
    }
    exit(0);
}

void listdir(char *path, unsigned int flag)
{
    DIR *dfd = (DIR *) malloc(sizeof(DIR));
    struct dirent *dp = (struct dirent *) malloc(sizeof(struct dirent));
    struct stat *stbuf = (struct stat *) malloc(sizeof(struct stat));
    char newpath[PATH_LEN];
    
    if (stat(path, stbuf) == -1)
        error("%s: No such file or directory", path);
    
    switch (stbuf->st_mode & S_IFMT)
    {
    case S_IFDIR:
        if ((dfd = opendir(path)) == NULL)
            error("%s: Can't access to the file or directory", path);
        while ((dp = readdir(dfd)) != NULL)
        {
            if (!(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")))
                continue;
            
            if (flag & FLAG_SZ)
            {
                sprintf(newpath, "%s/%s", path, dp->d_name);
                printf("%lld ", fsize(newpath));
            }
            printf("%s\n", dp->d_name);
        }
        break;
    case S_IFREG:
        if (flag & FLAG_SZ)
            printf("%lld ", fsize(path));
        break;
    default:
        break;
    }

    free(dfd);
    free(dp);
    free(stbuf);
}

static unsigned int getflag(char *str)
{
    int flag = 0;
    if (*str == '-')
    {
        while (*++str)
        {
            switch (*str)
            {
            case 'l':
                flag |= FLAG_LG;
                break;
            case 's':
                flag |= FLAG_SZ;
                break;
            default:
                error("illegal option -- %c", *str);
                break;
            }
        }
    }
    return flag;
}

static off_t fsize(char *path)
{
    off_t size = 0;
    DIR *dfd = (DIR *) malloc(sizeof(DIR));
    struct dirent *dp = (struct dirent *) malloc(sizeof(struct dirent));
    struct stat *stbuf = (struct stat *) malloc(sizeof(struct stat));
    char newpath[PATH_LEN];

    stat(path, stbuf);
    switch (stbuf->st_mode & S_IFMT)
    {
    case S_IFDIR:
        if ((dfd = opendir(path)) == NULL)
            error("%s: Can't access to the file or directory", path);
        while ((dp = readdir(dfd)) != NULL)
        {
            if (!(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")))
                continue;
            sprintf(newpath, "%s/%s", path, dp->d_name);
            size += fsize(newpath);
        }
        break;
    case S_IFREG:
        size += stbuf->st_size;
        break;
    default:
        break;
    }

    free(dfd);
    free(dp);
    free(stbuf);
    return size;
}

static void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s: ", prog);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    exit(1);
}

