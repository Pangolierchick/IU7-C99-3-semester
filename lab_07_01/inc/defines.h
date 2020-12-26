#ifndef __DEFINES_H__
#define __DEFINES_H__

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

#define ELEM_MAX(a, b, i)  \
    if (a.val < b)    \
    {                 \
        a.val = b;    \
        a.ind = i;    \
    }                 \

#define ELEM_MIN(a, b, i)  \
    if (a.val > b)    \
    {                 \
        a.val = b;    \
        a.ind = i;    \
    }                 \

#define FILE_IN argv[1]
#define FILE_OUT argv[2]
#define FILTER argv[3]

#define FILTER_KEY "f"

#endif // __DEFINES_H__
