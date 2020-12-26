#include <string.h>
#include <math.h>
#include "matrix_public.h"
#include "matrix_private.h"
#include "logger.h"
#include "my_error.h"
#include "io.h"

int matrix_errno;

matrix_t *init_matrix(int row, int clm)
{
    DBG_PRINT("Initializing matrix %dx%d\n", row, clm);

    matrix_t *matrix = malloc(sizeof(matrix_t));

    if (matrix == NULL)
        return NULL;

    matrix->matrix = malloc(sizeof(matrix_type *) * row);

    if (matrix->matrix == NULL)
        return NULL;

    matrix->alloc_row = 0;
    matrix->alloc_clm = clm;

    for (int i = 0; i < row; i++)
    {
        matrix->matrix[i] = malloc(sizeof(matrix_type) * clm);

        if (matrix->matrix[i] == NULL)
        {
            clean_matrix(matrix);
            return NULL;
        }
        matrix->alloc_row++;
    }

    

    matrix->clm = 0;
    matrix->row = 0;

    DBG_PRINT("Matrix initialized %p\n", GENERIC_POINTER(matrix));

    return matrix;
}

void clean_matrix(matrix_t *matrix)
{
    DBG_PRINT("Cleaning matrix %p\n", GENERIC_POINTER(matrix));
    if (matrix)
    {
        for (int i = 0; i < matrix->alloc_row; i++)
            free(matrix->matrix[i]);

        free(matrix->matrix);
        free(matrix);
    }
}

static void matrix_min(matrix_t *matrix, int *mrow, int *mclm)
{
    int min = matrix->matrix[0][0];
    *mrow = 0;
    *mclm = 0;

    DBG_PRINT("start min elem %d\n", min);

    int clm = 0;
    int row = 1;

    while (clm < matrix->clm)
    {
        while (row < matrix->row)
        {
            if (matrix->matrix[row][clm] <= min)
            {
                *mrow = row;
                *mclm = clm;
                min = matrix->matrix[row][clm];
            }

            row++;
        }

        row = 0;
        clm++;
    }

    DBG_PRINT("end min elem [%d][%d] = %d\n", *mrow, *mclm, min);
}

static void left_shift(int *vec, int len, int ind)
{
    for (int i = ind + 1; i < len; i++)
        vec[i - 1] = vec[i];
}

void delete_row(matrix_t *matrix, int ind)
{
    free(matrix->matrix[ind]);

    for (int row = ind + 1; row < matrix->row; row++)
    {
        matrix->matrix[row - 1] = matrix->matrix[row];
    }

    matrix->row--;
    matrix->alloc_row--;
}

void delete_clm(matrix_t *matrix, int ind)
{
    for (int row = 0; row < matrix->row; row++)
        left_shift(matrix->matrix[row], matrix->clm, ind);

    matrix->clm--;
}

matrix_t *squarize(matrix_t *matrix)
{
    if (matrix->clm == matrix->row)
        return matrix;

    int drow;
    int dclm;

    matrix_min(matrix, &drow, &dclm);

    if (matrix->clm < matrix->row)
        delete_row(matrix, drow);
    else
        delete_clm(matrix, dclm);

    return squarize(matrix);
}

int elm_geom_mean(matrix_t *matrix, int clm)
{
    size_t mean = abs(matrix->matrix[0][clm]);
    int prow = 1;

    while (prow < matrix->row)
        mean *= abs(matrix->matrix[prow++][clm]);

    return floor(pow(mean, 1.0 / (double) prow));
}

int add_rows(matrix_t *matrix, int rows)
{
    int row_iter = rows - matrix->row;

    DBG_PRINT("Adding %d rows\n", row_iter);

    while (row_iter--)
    {
        if (matrix->row >= matrix->alloc_row)
        {
            matrix->matrix = INCREASE_ROW(matrix);
            DBG_PRINT("Realloced: %d\t%d\n", matrix->row, matrix->alloc_row);

            if (matrix->matrix == NULL)
                return ALLOC_FAILED;

            int begin = matrix->alloc_row;

            matrix->alloc_row *= 2;

            for (int i = begin; i < matrix->alloc_row; i++)
            {
                if ((matrix->matrix[i] = malloc(sizeof(int) * matrix->alloc_clm)) == NULL)
                    return ALLOC_FAILED;
            }
        }


        for (int i = 0; i < matrix->clm; i++)
        {
            int curr_mean = elm_geom_mean(matrix, i);
            DBG_PRINT("Mean[%d][%d] = %d\n", matrix->row, i, curr_mean);

            matrix->matrix[matrix->row][i] = curr_mean;
        }

        matrix->row++;
    }

    return NO_ERROR;
}

/*
    1   2   3
    ^
    4   5   6
    ^
    9   3   0
            ^
*/

int row_min(matrix_t *matrix, int row)
{
    int min = matrix->matrix[row][0];

    for (int clm = 1; clm < matrix->clm; clm++)
        min = MIN(min, matrix->matrix[row][clm]);

    return min;
}

int realloc_row(matrix_t *matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        matrix->matrix[i] = INCREASE_CLM(matrix, i);
        if (matrix->matrix[i] == NULL)
            return ALLOC_FAILED;
    }

    matrix->alloc_clm *= 2;
    return NO_ERROR;
}

int add_clms(matrix_t *matrix, int clms)
{
    int clm_iter = clms - matrix->clm;

    DBG_PRINT("Adding %d columns\n", clm_iter);

    while (clm_iter--)
    {
        if (matrix->clm >= matrix->alloc_clm)
        {
            if (realloc_row(matrix))
                return ALLOC_FAILED;

            DBG_PRINT("Realloced: %d\t%d\n", matrix->clm, matrix->alloc_clm);
        }

        for (int row = 0; row < matrix->row; row++)
        {
            int curr_min = row_min(matrix, row);
            matrix->matrix[row][matrix->clm] = curr_min;

            DBG_PRINT("Min[%d][%d] = %d\n", matrix->clm, row, curr_min);
        }

        matrix->clm++;
    }

    return NO_ERROR;
}

matrix_t *enlarge(matrix_t *matrix, int nsize)
{
    int res = 0;

    if (matrix->row < nsize)
    {
        res = add_rows(matrix, nsize);
        res |= add_clms(matrix, nsize);
    }

    if (res)
    {
        matrix_errno = ALLOC_FAILED;
        return NULL;
    }

    return matrix;
}

static inline void matrixcpy(matrix_t *dst, const matrix_t *src)
{
    for (int i = 0; i < dst->alloc_clm; i++)
        for (int j = 0; j < dst->alloc_row; j++)
            dst->matrix[i][j] = src->matrix[i][j];

    dst->clm = src->clm;
    dst->row = src->row;
}

matrix_t *matrix_pow(matrix_t *matrix, int power)
{
    DBG_PRINT("Powering matrix %p in %d\n", GENERIC_POINTER(matrix), power);

    if (power < 0)
        return NULL;

    matrix_t *res = init_matrix(matrix->row, matrix->clm);

    if (res == NULL)
        return NULL;

    res->clm = matrix->clm;
    res->row = matrix->row;

    if (power == 0)
    {
        for (int i = 0; i < res->alloc_row; i++)
            for (int j = 0; j < res->alloc_clm; j++)
            {
                if (i == j)
                    res->matrix[i][j] = 1;
                else
                    res->matrix[i][j] = 0;
            }

        return res;
    }

    if (power == 1)
    {
        matrixcpy(res, matrix);

        return res;
    }

    matrix_t *sum = init_matrix(matrix->row, matrix->clm);

    if (sum == NULL)
        return NULL;

    matrixcpy(sum, matrix);

    for (int i = 0; i < power - 1; i++)
    {
        multiplication(sum, matrix, res);
        matrixcpy(sum, res);
    }

    clean_matrix(sum);

    return res;
}

void multiplication(const matrix_t *matrix1, const matrix_t *matrix2, matrix_t *res)
{
    for (int i = 0; i < res->alloc_row; i++)
        for (int j = 0; j < res->alloc_clm; j++)
            res->matrix[i][j] = 0;

    for (int i = 0; i < matrix1->row; i++)
        for (int j = 0; j < matrix2->clm; j++)
            for (int k = 0; k < matrix1->clm; k++)
                res->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];

    res->row = matrix1->row;
    res->clm = matrix2->clm;
}

int multiplication_task(matrix_t *matrix1, matrix_t *matrix2, matrix_t **res)
{
    int y;
    int p;

    printf("Input p: ");

    if (scanf("%d", &p) != 1)
        return BAD_P;

    if (p < 0)
        return BAD_P;

    printf("Input y: ");

    if (scanf("%d", &y) != 1)
        return BAD_Y;

    if (y < 0)
        return BAD_Y;

    DBG_PRINT("P = %d\tY = %d\n", p, y);

    matrix_t *matrix1_m = matrix_pow(matrix1, p);
    matrix_t *matrix2_m = matrix_pow(matrix2, y);

    if (matrix1_m == NULL || matrix2_m == NULL)
        return ALLOC_FAILED;

#if DEBUG    
    puts("----------------------------");
    print_matrix(matrix1_m);
    print_matrix(matrix2_m);
    puts("----------------------------");
#endif

    *res = init_matrix(matrix1->row, matrix1->clm);

    if (*res == NULL)
    {
        clean_matrix(matrix1_m);
        clean_matrix(matrix2_m);
        return ALLOC_FAILED;
    }

    multiplication(matrix1_m, matrix2_m, *res);

    clean_matrix(matrix1_m);
    clean_matrix(matrix2_m);

    return NO_ERROR;
}
