#ifndef __LIBARR_H__
#define __LIBARR_H__

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

EXPORT
int arr_lshift(int *arr, int len, int k);

EXPORT
int arr_nonsqr(int *arr, int len, int *new, int new_len);

#endif // __LIBARR_H__
