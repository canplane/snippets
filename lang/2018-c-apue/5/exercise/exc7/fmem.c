#include    "fmem.h"

FILE *
_fmemopen(void *restrict buf, size_t size, const char *restrict type)
{
    struct _fmemst *cookie = (struct _fmemst *)malloc(sizeof(struct _fmemst));

    if (buf == NULL) {
        cookie->_mode   = _DEFLT;
        buf             = malloc(BUFSIZ);
        *(char *)buf    = '\0';
    }
    else
        cookie->_mode   = 0;
    cookie->_base   = (char *)buf;
    if (size <= 0)
        return NULL;
    cookie->_size   = size;

    switch (*type++)
    {
    case 'r':
        cookie->_ptr    = (char *)buf;
        cookie->_mode   |= _MEMRD;
        break;
    case 'w':
        *cookie->_base  = '\0';
        cookie->_ptr    = (char *)buf;
        cookie->_mode   |= _MEMWR;
        break;
    case 'a':
        cookie->_mode   |= (_MEMWR | _MEMAP);
        for (cookie->_ptr = cookie->_base; *cookie->_ptr && \
            cookie->_ptr < cookie->_base + cookie->_size; (cookie->_ptr)++);
        cookie->_maxptr = cookie->_ptr;
        break;
    default:
        return NULL;
    }
    switch (*type++)
    {
    case '\0':
        break;
    case '+':
        cookie->_mode |= (_MEMRD | _MEMWR);
        if (*type++ == 'b') {
            cookie->_mode |= _ISBIN;
            if (!(*type))
                return NULL;
        }
        break;
    case 'b':
        cookie->_mode |= _ISBIN;
        if (*type++ == '+') {
            cookie->_mode |= (_MEMRD | _MEMWR);
            if (!(*type))
                return NULL;
        }
        break;
    default:
        return NULL;
    }
    
    cookie->_maxptr = cookie->_ptr;

    return funopen((const void *)cookie, _fmemread, _fmemwrite, _fmemseek, _fmemclose);
}

static int
_fmemread(void *cookie, char *buf, int nbytes)
{
    struct _fmemst *st = (struct _fmemst *)cookie;
    if (st->_mode & _MEMAP)
        st->_ptr = st->_maxptr;
    char            *whence = st->_ptr;
    if (!(st->_mode & _MEMRD))
        return -1;
    
    while (*whence && nbytes > 0 && (st->_ptr - st->_base) < st->_size - 1) {
        *buf++ = *st->_ptr++;
        nbytes--;
    }
    *buf = '\0';
    return (int)(st->_ptr - whence);
}

static int
_fmemwrite(void *cookie, const char *buf, int nbytes)
{
    struct _fmemst *st = (struct _fmemst *)cookie;
    if (st->_mode & _MEMAP)
        st->_ptr = st->_maxptr;
    char            *whence = st->_ptr;
    if (!(st->_mode & _MEMWR))
        return -1;
    while (nbytes > 0 && (st->_ptr - st->_base) < st->_size - 1) {
        *(st->_ptr++) = *buf++;
        nbytes--;
    }
    if (st->_mode & _MEMAP || st->_maxptr < st->_ptr) {
        st->_maxptr = st->_ptr;
        *st->_ptr   = '\0';
    }
    return (int)(st->_ptr - whence);
}

static fpos_t
_fmemseek(void *cookie, fpos_t pos, int whence)
{
    struct _fmemst *st = (struct _fmemst *)cookie;
    switch (whence)
    {
    case SEEK_SET:
        st->_ptr = st->_base + pos;
        break;
    case SEEK_CUR:
        st->_ptr += pos;
        break; 
    case SEEK_END:
        st->_ptr = st->_base + st->_size + pos;
        break;
    }
    return (fpos_t)(st->_ptr - st->_base);
}

static int
_fmemclose(void *cookie)
{
    struct _fmemst *st = (struct _fmemst *)cookie;
    if (st->_mode & _DEFLT)
        free(st->_base);
    free(st);
    return 0;
}
