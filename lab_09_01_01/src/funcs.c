#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "funcs.h"
#include "myerror.h"
#include "logger.h"

#define FREE_STRS(a, b)     \
    do                      \
    {                       \
        if (a)              \
            free(a);        \
        if (b)              \
            free(b);        \
    } while (0);            \
    
    

#define _GNU_SOURCE

int safe_atoi(const char *str, int *dst)
{
    char *end;
    *dst = (int) strtol(str, &end, 10);

    if (*end != '\0' && *end != '\n')
        return FAILED;

    return SUCCESS;
}

static void print_film(vector_type vec)
{
    printf("%s\n%s\n%d\n", vec.title, vec.name, vec.year);
}

static int title_cmp(const void *p1, const void *p2)
{
    return strcmp(((char*) p1), ((film_t*) p2)->title);
}

static int name_cmp(const void *p1, const void *p2)
{
    return strcmp(((char*) p1), ((film_t*) p2)->name);
}

static int year_cmp(const void *p1, const void *p2)
{
    return (*((int *) p1) - ((film_t*) p2)->year);
}

void print_vec(vector_t *vec)
{
    for (int i = 0; i < vec->len; i++)
        print_film(vec->vec[i]);
}

int vector_sorted_insert(vector_t *vec, const vector_type *val, const int field)
{
    if (vec->len == 0)
        return append(vec, val);

    int if_exit = FALSE;
    int ind = 0;

    while (!if_exit && (ind < vec->len))
    {
        switch (field)
        {
            case TITLE:
                if (strcmp(val->title, vec->vec[ind].title) < 0)
                    if_exit = TRUE;
                break;
            case NAME:
                if (strcmp(val->name, vec->vec[ind].name) < 0)
                    if_exit = TRUE;
                break;
            case YEAR:
                if (val->year < vec->vec[ind].year)
                {
                    if_exit = TRUE;
                }
                break;
        }
        if (!if_exit)
            ind++;
    }

    if (!if_exit)
        return append(vec, val);

    return insert(vec, val, ind);
}

int insert_str_field(vector_type *elem, char *line, int len, int field)
{
    if (len == EOF && errno == 0)
        return FILE_END;

    if (len == EOF && errno)
    {
        return BAD_FILE;
    }

    if (len == 1 && *line == '\n')
        return BAD_FILE;
    
    char *pfield = NULL;

    if (field == TITLE)
        pfield = elem->title;
    else
        pfield = elem->name;
    
    pfield = malloc(sizeof(char) * len);
    
    if (pfield == NULL)
    {
        return ALLOCATION_FAULT;
    }
    
    memcpy(pfield, line, len);

    if (pfield[len - 1] == '\n')
        pfield[len - 1] = '\0';
    
    if (field == TITLE)
        elem->title = pfield;
    else
        elem->name = pfield;

    return NO_ERROR;
}

int read_one_struct(FILE *f, vector_t *vec, const int field)
{
    vector_type tmp_struct = { .name = NULL, .title = NULL, .year = 0 };
    
    char *line_buff = NULL;
    size_t line_len = 0;
    int cpy_len;

    errno = 0;

    cpy_len = getdelim(&line_buff, &line_len, '\n', f);
    
    DBG_PRINT("Readed line (%d): %s\n", cpy_len, line_buff);
    
    int res = insert_str_field(&tmp_struct, line_buff, cpy_len, TITLE);
    DBG_PRINT("Insert code: %d\n", res);

    if (res)
    {
        free(line_buff);
        return res;
    }

    cpy_len = getdelim(&line_buff, &line_len, '\n', f);
    
    DBG_PRINT("Readed line (%d): %s\n", cpy_len, line_buff);
    
    res = insert_str_field(&tmp_struct, line_buff, cpy_len, NAME);
    DBG_PRINT("Insert code: %d\n", res);

    if (res)
    {
        free(line_buff);
        FREE_STRS(tmp_struct.title, NULL);
        return res;
    }

    cpy_len = getdelim(&line_buff, &line_len, '\n', f);

    if (safe_atoi(line_buff, &tmp_struct.year))
    {
        free(line_buff);
        FREE_STRS(tmp_struct.title, tmp_struct.name);
        return BAD_FILE;
    }

    DBG_PRINT("Readed year: %d\n", tmp_struct.year);

    if (tmp_struct.year <= 0)
    {
        free(line_buff);
        FREE_STRS(tmp_struct.title, tmp_struct.name);
        return BAD_FILE;
    }
    
    
    res = vector_sorted_insert(vec, &tmp_struct, field);

    free(line_buff);
    
    return res;
}

int read_file(FILE *f, vector_t *vec, const int field)
{
    int res;
    int i = 0;
    while ((res = read_one_struct(f, vec, field)) == 0)
        i++;
    
    if (res != FILE_END)
        return FAILED;

    return SUCCESS;
}

int myfind(const void *key, const vector_t *vec, cmp_fun *fun, const int field)
{
    vector_type *s_res = NULL;
    const void *p_key = key;
    int s_year = 0;

    switch (field)
    {
        case TITLE:
        case NAME:
            break;
        case YEAR:
            if (safe_atoi(key, &s_year))
                return BAD_ARGS;
            
            p_key = (void *) &s_year;
            break;
    }

    s_res = bsearch(p_key, vec->vec, vec->len, sizeof(vector_type), fun);

    if (s_res == NULL)
        puts("Not found");
    else
        print_film(*s_res);

    return SUCCESS;
}

int parse_args(const int argc, const char **argv, parsed_args_t *pa)
{
    if (argc < 3 || argc > 4)
        return BAD_ARGS;

    if (!strcmp(TITLE_STR, FIELD))
    {
        pa->cmp_func = title_cmp;
        pa->field = TITLE;
    }
    else if (!strcmp(NAME_STR, FIELD))
    {
        pa->cmp_func = name_cmp;
        pa->field = NAME;
    }
    else if (!strcmp(YEAR_STR, FIELD))
    {
        pa->cmp_func = year_cmp;
        pa->field = YEAR;
    }
    else
        return BAD_ARGS;

    FILE *f = fopen(FILENAME, "r");

    if (f == NULL)
        return UNEXISTING_FILENAME;

    pa->f = f;

    return NO_ERROR;
}

