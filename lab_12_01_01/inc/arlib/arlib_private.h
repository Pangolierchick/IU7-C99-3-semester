#ifndef __ARLIB_PRIVATE_H__
#define __ARLIB_PRIVATE_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define SWAP(a, b, size)             \
    do                               \
    {                                \
        size_t __size = (size);      \
        char *__a = (a), *__b = (b); \
        do                           \
        {                            \
            char __tmp = *__a;       \
            *__a++ = *__b;           \
            *__b++ = __tmp;          \
        } while (--__size > 0);      \
    } while (0)                      \

typedef struct array_elem_s
{
    int val;
    int ind;
} array_elem_t;

int int_cmp(const void *a, const void *b);
void array_min_max(const int *arr_b, const int *arr_e, array_elem_t *p_min, array_elem_t *p_max);

#endif // __ARLIB_PRIVATE_H__
