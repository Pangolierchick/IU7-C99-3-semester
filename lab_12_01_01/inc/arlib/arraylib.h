#ifndef __ARRAYLIB_H__
#define __ARRAYLIB_H__

#ifdef OSX

#define EXPORT __attribute__((visibility("default")))

#elif defined(WIN)

#pragma message "TODO"

#elif defined(LINUX)

#pragma message "TODO"

#else
#warning "Unknown sybsytem";
#define EXPORT
#endif

extern int mysort_errno;

typedef int cmp_fun(const void*, const void*);

EXPORT
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

EXPORT
void print_arr(const int *arr_b, const int *arr_e);

/*
    base -- array
    __nel -- len
    __width -- sizeof of one elem of base
    cmp -- cmp func
*/
EXPORT
void mysort(void *base, size_t __nel, size_t __width, cmp_fun cmp);

#endif // __ARRAYLIB_H__
