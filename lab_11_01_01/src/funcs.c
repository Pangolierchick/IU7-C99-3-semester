#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "mystring.h"

size_t myitoa(int val, char *src, size_t len, int base)
{
    if (base < 2)
        return 0;
    
    if (len == 0)
        return 0;

    size_t written = 0;
    int neg = val < 0 && base == 10;

    if (neg && base == 10)
    {
        val = -val;
        src++;
    }

    unsigned int uval = val;
 
    do
    {
        int symb = uval % base;

        if (symb < 10)
            symb += '0';
        else
            symb += 'W';
        
        src[written++] = symb;
        uval /= base;
    } while (uval && written < len - 1);

    if (written == len - 1 && uval)
        return EOF;

    src[written] = '\0';
    mystrrev(src);
    
    if (neg)
    {
        src--;
        src[0] = '-';
        written++;
    }

    return written;
}




