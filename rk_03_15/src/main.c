#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
#include "funcs.h"
#include "logger.h"

#if DEBUG
int res;

void print_exit(void)
{
    DBG_PRINT("Exitting: %d\n", res); // ???
}
#endif 

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

#if DEBUG == 0
    int res;
#else
    atexit(print_exit);
#endif

    FILE *fi = fopen(INPUT_FILENAME, "r");
    FILE *fo = fopen(OUTPUT_FILENAME, "w");

    if (fi == NULL || fo == NULL)
        return 5;
    
    matrix_t *matrix = NULL;

    res = read_from_file(fi, &matrix);

    if (res)
    {
        clean_matrix(matrix);
        fclose(fi);
        fclose(fo);

        return res;
    }

    int elems = change_zeroes(matrix);

#if DEBUG
    puts("---------- PRINTING ----------");
    print_matrix(matrix);
    puts("------------------------------");
#endif

    DBG_PRINT("Changed: %d\n", elems);

    int del = del_row(matrix);

    DBG_PRINT("Deleted: %d\n", del);

#if DEBUG
    puts("---------- PRINTING ----------");
    print_matrix(matrix);
    puts("------------------------------");
#endif

    print_in_file(fo, matrix);

    clean_matrix(matrix);

    return fclose(fi) == EOF || fclose(fo) == EOF;
}
