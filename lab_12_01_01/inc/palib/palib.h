#ifndef __PALIB_H__
#define __PALIB_H__

#include <stdio.h>
#include <stdbool.h>
#include "palib_errors.h"

#ifdef OSX
#define EXPORT __attribute__((visibility("default")))

#elif defined(WIN)

#pragma message "TODO"

#elif defined(LINUX)

#pragma message "TODO"

#else
#define EXPORT
#warning "Unknown sybsytem";
#endif // OSX

typedef struct pa_args_s
{
    FILE *fi;
    FILE *fo;
    bool filter;
} pa_args_t;


#define FILE_IN     argv[1]
#define FILE_OUT    argv[2]
#define FILTER      argv[3]

#define FILTER_KEY  "f"

EXPORT
int parse_args(int argc, char **argv, pa_args_t *pa);

#endif // __PALIB_H__
