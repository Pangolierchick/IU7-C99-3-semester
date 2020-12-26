#ifndef __FUNCS_H__
#define __FUNCS_H__

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

extern int mysort_errno;

typedef struct array_elem_s
{
    int val;
    int ind;
} array_elem_t;

typedef struct pa_args_s
{
    FILE *fi;
    FILE *fo;
    bool filter;
} pa_args_t;

typedef int cmp_fun(const void*, const void*);

int int_cmp(const void *a, const void *b);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int parse_args(int argc, char **argv, pa_args_t *pa);
void print_arr(const int *arr_b, const int *arr_e);
/*
    base -- array
    __nel -- len
    __width -- sizeof of one elem of base
    cmp -- cmp func
*/
void mysort(void *base, size_t __nel, size_t __width, cmp_fun cmp);
void array_min_max(const int *arr_b, const int *arr_e, array_elem_t *p_min, array_elem_t *p_max);

#endif // __FUNCS_H__
