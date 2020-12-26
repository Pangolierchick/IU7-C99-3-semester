#ifndef __FUNCS_H__
#define __FUNCS_H__

typedef struct matrix_s
{
    int **matrix;

    int clm;
    int row;

    int alloc_clm;
    int alloc_row;
} matrix_t;

matrix_t *init_matrix(int row, int clm);
void clean_matrix(matrix_t *matrix);

int del_row(matrix_t *matrix);
int change_zeroes(matrix_t *matrix);

void print_matrix(matrix_t *matrix);

int read_from_file(FILE *f, matrix_t **matrix);
void print_in_file(FILE *f, matrix_t *matrix);

#endif // __FUNCS_H__
