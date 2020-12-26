#ifndef __FUNCS_H__
#define __FUNCS_H__

#include <stdio.h>
#include "vector.h"

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

int safe_atoi(const char *str, int *dst);
int myfind(const void *key, const vector_t *vec, cmp_fun *fun, const int field);
void print_vec(vector_t *vec);
int read_file(FILE *f, vector_t *vec, const int field);
int parse_args(const int argc, const char **argv, parsed_args_t *pa);
int read_one_struct(FILE *f, vector_t *vec, const int field);
int vector_sorted_insert(vector_t *vec, const vector_type *val, const int field);

#endif // __FUNCS_H__
