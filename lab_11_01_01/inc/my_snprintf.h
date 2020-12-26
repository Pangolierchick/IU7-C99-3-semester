#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stdlib.h>
#include <stdarg.h>

#define INT_SPEC                'd'
#define CHAR_SPEC               'c'
#define HEX_SPEC                'x'
#define STRING_SPEC             's'

#define DEC_BUFF_LEN            20

int my_snprintf(char *dst, size_t size, const char *format, ...);

#endif // __MY_SNPRINTF_H__
