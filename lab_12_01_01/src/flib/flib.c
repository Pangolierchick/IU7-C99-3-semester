#include <stdlib.h>
#include <stdio.h>
#include "flib_errors.h"
#include "macrologger.h"
#include "filelib.h"
#include "filelib_private.h"

EXPORT
int read_file(FILE *f, int **pb, int **pe)
{
    if (f == NULL || pb == NULL || pe == NULL)
        return -1;
    rewind(f);

    int len;
    if (get_file_len(f, &len))
        return BAD_FILE;

    LOG_DEBUG("File len %d\n", len);
    
    if (!len)
        return EMPTY_FILE;

    rewind(f);

    *pb = (int *) malloc(sizeof(int) * len);

    if (*pb == NULL)
        return ALLOCATION_FAULT;

    int *ppb = *pb;
    int res = 1;

    int clen = len;

    while (clen-- && res != EOF)
        res = fscanf(f, "%d", ppb++);

    *pe = *pb + len;

    return NO_ERROR;
}

EXPORT
int write_file(FILE *f, int *pb, int *pe)
{
    if (f == NULL || pb == NULL || pe == NULL)
        return -1;
    int *ppb = pb;
    int len = pe - pb;

    int res = 1;

    while (len-- && res != EOF)
    {
        res = fprintf(f, "%d ", *ppb++);

        if (!res)
            return FILE_IO_FAILED;
    }

    fprintf(f, "\n");

    return NO_ERROR;
}

int get_file_len(FILE *f, int *len)
{
    *len = 0;
    int dummy;
    int res = 0;

    while (res != EOF)
    {
        res = fscanf(f, "%d", &dummy);
        
        if (!res)
            return BAD_FILE;

        if (res == 1)
            (*len)++;
    }

    return NO_ERROR;
}
