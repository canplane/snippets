#ifndef __DATA_H__
#define __DATA_H__

#include <stdio.h>
#include <stdarg.h>

#include "../14_hash/hash.c"
/*
typedef struct {
    int key;
} Element;

void setData(Element data[], int size, ...)
{
    va_list ap;
    va_start(ap, size);
    while (size--)
        (data++)->key = va_arg(ap, int);    
    va_end(ap);
}

void printData(Element data[], int size)
{
    while (size--)
        printf("%d ", (data++)->key);
    printf("\n");
}
*/

#endif