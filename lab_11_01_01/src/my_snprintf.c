#include <stdlib.h>
#include "my_snprintf.h"
#include "funcs.h"
#include "mystring.h"
#include "logger.h"

static inline int write_buff(char *dst, const char *src, int written, int len, int to_write)
{
    int i = 0;
    while (written < len - 1 && i < to_write)
    {
        dst[written++] = *src++;
        i++;
    }

    return i;
}

int my_snprintf(char *dst, size_t size, const char *format, ...)
{
    const char *pformat = format;
    size_t written = 0;
    size_t readed = 0;

    if (format == NULL)
        return EOF;

    if (size == 0)
        size++;

    va_list va;
    va_start(va, format);

    while (*pformat)
    {
        if (*pformat == '%')
        {
            pformat++;

            if (*pformat == '\0')
                break;

            DBG_PRINT("Found %% and %c\n", *pformat);

            switch (*pformat)
            {  
                case INT_SPEC:
                    {
                        int num = va_arg(va, int);

                        char str_num[DEC_BUFF_LEN];

                        size_t needed_space = myitoa(num, str_num, DEC_BUFF_LEN, DEC);
                        size_t copied = mymemcpy(dst + written, str_num, MIN(needed_space, (size - 1 - written)));

                        written += copied;
                        readed += needed_space;

                        pformat++;
                        break;
                    }
                case CHAR_SPEC:
                    {
                        unsigned char num = va_arg(va, int);

                        if (written < size - 1)
                            dst[written++] = num;    
                        
                        readed++;
                        pformat++;
                        break;
                    }
                case HEX_SPEC:
                    {
                        int num = va_arg(va, int);

                        char str_num[DEC_BUFF_LEN];

                        size_t needed_space = myitoa(num, str_num, DEC_BUFF_LEN, HEX);

                        size_t copied = mymemcpy(dst + written, str_num, sizeof(char) * MIN(needed_space, (size - 1 - written)));

                        written += copied;
                        readed += needed_space;

                        pformat++;
                        break;
                    }
                case STRING_SPEC:
                    {
                        const char *str = va_arg(va, const char *);
                        
                        size_t need_len = mystrlen(str);

                        DBG_PRINT("written: %zu\n", written);
                        DBG_PRINT("Need len: %zu\t last: %zu\n", need_len, MIN(need_len, (size - 1 - written)));
                        
                        size_t copied = mymemcpy(dst + written, str, MIN(need_len, (size - 1 - written)));
                        
                        readed += need_len;
                        written += copied;
                        pformat++;
                        break;
                    }
            }
        }
        else
        {
            written += write_buff(dst, pformat, written, size, 1);
            readed++;
            pformat++;
        }
    }

    va_end(va);

    if (dst)
        dst[written] = '\0';

    return readed;
}
