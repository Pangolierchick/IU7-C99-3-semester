#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcs.h"
#include "my_error.h"
#include "logger.h"

void print_film(const void *src)
{
    film_t *psrc = (film_t *) src;

    printf("%s\n", psrc->title);
    printf("%s\n", psrc->name);
    printf("%d\n", psrc->year);
}

int cmp_film_by_year(const void *a, const void *b)
{
    film_t *pa = (film_t *) a;
    film_t *pb = (film_t *) b;

    return pa->year - pb->year;
}

int cmp_film_by_name(const void *a, const void *b)
{
    film_t *pa = (film_t *) a;
    film_t *pb = (film_t *) b;

    return strcmp(pa->name, pb->name);
}

int read_struct(FILE *f, node_t **list)
{
    film_t *tmp_struct = malloc(sizeof(film_t));

    if (fgets(tmp_struct->title, TITLE_LEN, f) == NULL)
    {
        free(tmp_struct);
        return FILE_END;
    }
    tmp_struct->title[strcspn(tmp_struct->title, "\n")] = 0;

    DBG_PRINT("Title: %s\n", tmp_struct->title);

    if (fgets(tmp_struct->name, NAME_LEN, f) == NULL)
    {
        free(tmp_struct);
        return BAD_FILE;
    }
    tmp_struct->name[strcspn(tmp_struct->name, "\n")] = 0;

    DBG_PRINT("Name: %s\n", tmp_struct->name);

    if (!strlen(tmp_struct->title) || !strlen(tmp_struct->name))
    {
        free(tmp_struct);
        return BAD_FILE;
    }

    int res;

    if ((res = fscanf(f, "%d\n", &tmp_struct->year)) != 1)
    {
        free(tmp_struct);
        return BAD_FILE;
    }

    if (tmp_struct->year <= 0)
    {
        free(tmp_struct);
        return BAD_FILE;
    }

    DBG_PRINT("Year: %d\n", tmp_struct->year);

    pushback(list, tmp_struct);

    return NO_ERROR;
}

int read_file(FILE *f, node_t **list)
{
    int res;
    while ((res = read_struct(f, list)) == 0);

    if (res != FILE_END)
    {
        full_clear_list(list);
        return res;
    }
    
    return NO_ERROR;
}

int write_in_file(FILE *f, node_t *list)
{
    FOREACH(list, elem)
    {
        film_t *data = elem->data;

        fprintf(f, "%s\n%s\n%d\n", data->title, data->name, data->year);
    }

    return NO_ERROR;
}

char *parse_args(int argc, char **argv)
{
    return argc == 2 ? argv[1] : NULL;
}
