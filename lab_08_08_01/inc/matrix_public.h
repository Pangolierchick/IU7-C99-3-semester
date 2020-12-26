#ifndef __MATRIX_PUBLIC_H__
#define __MATRIX_PUBLIC_H__

#define MIN(a, b)                   (a < b ? a : b)
#define MAX(a, b)                   (a < b ? b : a)

#define GENERIC_POINTER(p)          (void *) p

#include <stdlib.h>

extern int matrix_errno;

typedef int matrix_type;

typedef struct matrix_s
{
    matrix_type **matrix;

    int clm;
    int row;

    int alloc_clm;
    int alloc_row;
} matrix_t;

void clean_matrix(matrix_t *matrix);
matrix_t *init_matrix(int row, int clm);

matrix_t *squarize(matrix_t *matrix);
matrix_t *enlarge(matrix_t *matrix, int nsize);

int multiplication_task(matrix_t *matrix1, matrix_t *matrix2, matrix_t **res);

#endif // __MATRIX_PUBLIC_H__
