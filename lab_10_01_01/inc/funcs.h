#ifndef __FUNCS_H__
#define __FUNCS_H__

#define TITLE_LEN               26
#define NAME_LEN                26

#include <stdio.h>
#include "list.h"

typedef int year_t;

typedef struct film_s
{
    char title[TITLE_LEN];
    char name[NAME_LEN];
    year_t year;
} film_t;


char *parse_args(int argc, char **argv);
void print_film(const void *src);
int cmp_film_by_year(const void *a, const void *b);
int cmp_film_by_name(const void *a, const void *b);

int read_struct(FILE *f, node_t **list);
int read_file(FILE *f, node_t **list);
int write_in_file(FILE *f, node_t *list);

#endif // __FUNCS_H__
