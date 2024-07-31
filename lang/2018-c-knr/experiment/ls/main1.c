#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLEN      100
#define FLAG_LG     01
#define FLAG_SZ     02
#define SZ_BLK(n)   (n)

void listdir(char *, unsigned int);
static void lprint(char *);
static unsigned int getflag(char *);
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
    char newpath[MAXLEN];
    
    if (stat(path, stbuf) == -1)
        error("%s: No such file or directory", path);
    
    switch (stbuf->st_mode & S_IFMT)
    {
    case S_IFDIR:
        if ((dfd = opendir(path)) == NULL)
            error("%s: Can't access to the file or directory", path);
        while ((dp = readdir(dfd)) != NULL)
        {
            if (dp->d_name[0] == '.')
                continue;
            if (flag & FLAG_SZ)
                printf("%lld ", SZ_BLK(stbuf->st_size));
            if (flag & FLAG_LG)
            {
                sprintf(newpath, "%s/%s", path, dp->d_name);
                lprint(newpath);
            }
            printf("%s\n", dp->d_name);
        }
        break;
    case S_IFREG:
        if (flag & FLAG_SZ)
            printf("%lld ", SZ_BLK(stbuf->st_size));
        if (flag & FLAG_LG)
            lprint(newpath);
        printf("%s\n", path);
        break;
    default:
        break;
    }

    free(dfd);
    free(dp);
    free(stbuf);
}

static void lprint(char *path)
{
    char temp[MAXLEN] = "", c;
    struct stat *stbuf = (struct stat *) malloc(sizeof(struct stat));
    mode_t d;
    if (stat(path, stbuf) == -1)
        error("%s: No such file or directory", path);

    switch (stbuf->st_mode & S_IFMT)
    {
    case S_IFDIR:
        strcat(temp, "d");
        break;
    case S_IFREG:
        strcat(temp, "-");
        break;
    default:
        strcat(temp, "?");
        break;
    }

    for (int i = 0, d = (stbuf->st_mode & 0777); i < 9; d <<= 1, i++)
        if (d & 0400)
        {
            switch (i % 3)
            {
            case 0:
                strcat(temp, "r");
                break;
            case 1:
                strcat(temp, "w");
                break;
            default:
                strcat(temp, "x");
                break;
            }
        }
        else
            strcat(temp, "-");
    
    sprintf(temp, "%s %d", temp, stbuf->st_nlink);
    sprintf(temp, "%s %lld", temp, stbuf->st_size);


    free(stbuf);
    printf("%s ", temp);
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

static void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "%s: ", prog);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    exit(1);
}

