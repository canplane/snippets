#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>          /* flags for read and write */
#include <sys/types.h>      /* typedefs */
#include <sys/stat.h>       /* structure returned by stat */
#include <sys/uio.h>

#define MAX_PATH    1024
#define NAME_MAX    14          /* longest filename component; */
                                /* system-depenent */

typedef struct {                
    long ino;                   
    char name[NAME_MAX+1];      
} Dirent;

typedef struct {                
    int fd;                     
    Dirent d;                   
} DIR;

#ifndef DIRSIZ
#define DIRSIZ      14
#endif
struct dirent                   
{
    ino_t d_ino;                
    char d_name[DIRSIZ];        
};

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));
DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);