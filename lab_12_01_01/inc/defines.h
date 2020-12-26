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


#endif // __DEFINES_H__
