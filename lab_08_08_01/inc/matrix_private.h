#ifndef __MATRIX_PRIVATE_H__
#define __MATRIX_PRIVATE_H__

#include "matrix_public.h"

#define INCREASE_ROW(matrix)        ((matrix_type **) realloc(matrix->matrix, sizeof(matrix_type *) * matrix->alloc_row * 2))
#define INCREASE_CLM(matrix, row)   ((matrix_type *)  realloc(matrix->matrix[row], sizeof(matrix_type) * matrix->alloc_clm * 2))

void delete_clm(matrix_t *matrix, int ind);
void delete_row(matrix_t *matrix, int ind);

int elm_geom_mean(matrix_t *matrix, int clm);

int row_min(matrix_t *matrix, int row);
int realloc_row(matrix_t *matrix);
int add_rows(matrix_t *matrix, int rows);
int add_clms(matrix_t *matrix, int clms);

matrix_t *matrix_pow(matrix_t *matrix, int power);
void multiplication(const matrix_t *matrix1, const matrix_t *matrix2, matrix_t *res);

#endif // __MATRIX_PRIVATE_H__
