#include "mystring.h"

#define SWAP_CHARS(a, b)    \
    do                      \
    {                       \
        char c = a;         \
        a = b;              \
        b = c;              \
    } while (0);            \
    

size_t mystrlen(const char *str)
{
    const char *pstr = str;

    while (*pstr++);

    return pstr - str - 1;
}


size_t mystrnlen(const char *str, size_t len)
{
    const char *pstr = str;
    size_t wlen = 0;

    while (*pstr++ && wlen++ < len);

    return pstr - str - 1;
}

size_t mystrncpy(char *dst, const char *src, size_t len)
{
    size_t written = 0;

    while (*dst && *src && written < len - 1)
    {
        *dst++ = *src++;
        written++;
    }

    *dst = '\0';

    return written;
}

void mystrrev(char *src)
{
    size_t len = mystrlen((const char *) src);
    size_t i = 0;
    size_t j = len - 1;

    while (i < j)
    {
        SWAP_CHARS(src[i], src[j]);

        i++;
        j--;
    }
}

size_t mymemcpy(void *dst, const void *src, size_t len)
{
    size_t written = 0;
    
    if (dst && src && len > 0)
    {
        char *pdst = dst;
        const char *psrc = src;

        while (written < len)
        {
            *pdst++ = *psrc++;
            written++;
        }
    }

    return written;
}
