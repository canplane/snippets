#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#define     fmemopen(buf, size, type)   (_fmemopen(buf, size, type))
#define     _MEMRD      01
#define     _MEMWR      02
#define     _MEMAP      04
#define     _ISBIN      010
#define     _DEFLT      020    

struct _fmemst {
    char    *_base;
    char    *_ptr;
    char    *_maxptr;
    fpos_t  _size;
    int     _mode;
};

FILE            *_fmemopen(void *, size_t, const char *);
static int      _fmemread(void *, char *, int);
static int      _fmemwrite(void *, const char *, int);
static fpos_t   _fmemseek(void *, fpos_t, int);
static int      _fmemclose(void *);
