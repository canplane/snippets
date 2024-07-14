#include <stdio.h>
#define setbuf(fp, buf)   __setbuf(buf, size)


void __setbuf(FILE *restrict fp, char *restrict buf)
{
    if (buf == NULL)
        setvbuf(fp, NULL, _IONBF, 0);
    else
        setvbuf(fp, buf, _IOFBF, BUFSIZ);
}


