#include <string.h>
#include <stdlib.h>
#include "funcs.h"
#include "error.h"

static int safe_atoi(const char *str, int *dst)
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

void print_vec(static_vector_t vec)
{
    for (int i = 0; i < vec.len; i++)
        print_film(vec.vec[i]);
}

int vector_sorted_insert(static_vector_t *vec, const vector_type val, const int field)
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
                if (strcmp(val.title, vec->vec[ind].title) < 0)
                    if_exit = TRUE;
                break;
            case NAME:
                if (strcmp(val.name, vec->vec[ind].name) < 0)
                    if_exit = TRUE;
                break;
            case YEAR:
                if (val.year < vec->vec[ind].year)
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

int read_one_struct(FILE *f, static_vector_t *vec, const int field)
{
    vector_type tmp_struct;
    // memset(&tmp_struct, 0, sizeof(vector_type));

    if (fgets(tmp_struct.title, TITLE_LEN, f) == NULL)
        return FILE_END;
    tmp_struct.title[strcspn(tmp_struct.title, "\n")] = 0;

    if (fgets(tmp_struct.name, NAME_LEN, f) == NULL)
        return BAD_FILE;
    tmp_struct.name[strcspn(tmp_struct.name, "\n")] = 0;

    if (!strlen(tmp_struct.title) || !strlen(tmp_struct.name))
        return BAD_FILE;

    int res;

    if ((res = fscanf(f, "%d\n", &tmp_struct.year)) != 1)
    {
        return BAD_FILE;
    }

    if (tmp_struct.year <= 0)
    {
        return BAD_FILE;
    }
    
    return vector_sorted_insert(vec, tmp_struct, field);
}

int read_file(FILE *f, static_vector_t *vec, const int field)
{
    int res;
    int i = 0;
    while ((res = read_one_struct(f, vec, field)) == 0)
        i++;
    
    if (res != FILE_END)
        return FAILED;

    return SUCCESS;
}

int myfgets(char *buff, int len, FILE *f)
{
    char c = 0;
    int len_ch = 0;
    while (1)
    {
        c = getc(f);

        if (c == EOF)
            return EOF;

        if (c == '\n' || len_ch > len - 1)
            break;
        buff[len_ch++] = c;
    }

    buff[len_ch++] = '\0';

    return len_ch;
}

int myfind(const void *key, const static_vector_t vec, cmp_fun *fun, const int field)
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

    s_res = bsearch(p_key, vec.vec, vec.len, sizeof(vector_type), fun);

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

