#ifndef __FUNCS_H__
#define __FUNCS_H__

#include <stdio.h>
#include "static_vector.h"

typedef int cmp_fun(const void*, const void*);

#define TITLE               0
#define NAME                1
#define YEAR                2

#define FALSE               0
#define TRUE                1

#define TITLE_STR       "title"
#define NAME_STR        "name"
#define YEAR_STR        "year"

#define FILENAME        argv[1]
#define FIELD           argv[2]
#define KEY             argv[3]

typedef struct parsed_args_s
{
    cmp_fun *cmp_func;
    int field;
    FILE *f;
} parsed_args_t;

int myfind(const void *key, const static_vector_t vec, cmp_fun *fun, const int field);
void print_vec(static_vector_t vec);
int read_file(FILE *f, static_vector_t *vec, const int field);
int myfgets(char *buff, int len, FILE *f);
int parse_args(const int argc, const char **argv, parsed_args_t *pa);
int read_one_struct(FILE *f, static_vector_t *vec, const int field);
int vector_sorted_insert(static_vector_t *vec, const vector_type val, const int field);

#endif // __FUNCS_H__