#ifndef __FUNCS_H__
#define __FUNCS_H__

#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// to not include large stdio.h
#ifndef EOF 
#define EOF             -1
#endif

#define DEC             10
#define HEX             16

size_t myitoa(int val, char *src, size_t len, int base);

#endif // __FUNCS_H__
