#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <stdlib.h>

size_t mystrnlen(const char *str, size_t len);
size_t mystrncpy(char *dst, const char *src, size_t len);
void mystrrev(char *src);
size_t mystrlen(const char *str);
size_t mymemcpy(void *dst, const void *src, size_t len);

#endif // __MYSTRING_H__
