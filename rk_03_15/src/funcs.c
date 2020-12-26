#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"
#include "defines.h"
#include "logger.h"

matrix_t *init_matrix(int row, int clm)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));

    if (matrix == NULL)
        return NULL;

    matrix->matrix = calloc(row, sizeof(int *));

    if (matrix->matrix == NULL)
    {
        free(matrix);
        return NULL;
    }

    matrix->alloc_clm = clm;
    matrix->alloc_row = 0;

    for (int c = 0; c < row; c++)
    {
        matrix->matrix[c] = malloc(sizeof(int) * clm);

        if (matrix->matrix[c] == NULL)
        {
            clean_matrix(matrix);
            return NULL;
        }

        matrix->alloc_row++;
    }

    matrix->clm = 0;
    matrix->row = 0;

    DBG_PRINT("Matrix inited %d %d, %p\n", row, clm, GENERICK_POINTER(matrix));

    return matrix;
}

void clean_matrix(matrix_t *matrix)
{
    if (matrix)
    {
        DBG_PRINT("Cleaning %d\n", matrix->alloc_row);
        for (int i = 0; i < matrix->alloc_row; i++)
        {
            DBG_PRINT("Cleaning %d\t%p\n", i, GENERICK_POINTER(matrix->matrix[i]));
            free(matrix->matrix[i]);
        }


        if (matrix->alloc_row)
            free(matrix->matrix);
        free(matrix);
        DBG_PRINT("Matrix cleaned %p\n", GENERICK_POINTER(matrix));
    }
}

int read_from_file(FILE *f, matrix_t **matrix)
{
    int row;
    int clm;

    if (fscanf(f, "%d %d", &row, &clm) != 2)
        return 1; // FIXME

    *matrix = init_matrix(row, clm);

    if (*matrix == NULL)
        return 2; // FIXME

    for (int i = 0; i < row; i++)
        for (int j = 0; j < clm; j++)
            if (fscanf(f, "%d", &(*matrix)->matrix[i][j]) != 1)
                return 3; // FIXME

    (*matrix)->row = row;
    (*matrix)->clm = clm;

    return 0;
}
//   1
// 1 2 3 4 5
//   ^
// 1 3 4 5

static inline void shift_left(int **arr, int len, int ind)
{
    if (len > 1)
    {
        free(arr[ind]);

        for (int i = ind + 1; i < len; i++)
            arr[i - 1] = arr[i];
    }
}

/*
    0   2   3

    0   0   0

    0   3   1
*/

int del_row(matrix_t *matrix)
{
    int deleted = 0;

    int row = matrix->row;
    int i = 0;

    while (row-- > 0)
    {
        bool_t all_zero = TRUE;
        for (int j = 0; j < matrix->alloc_clm; j++)
        {
            if (matrix->matrix[i][j])
                all_zero = FALSE;
        }
        
        if (all_zero)
        {
            deleted++;
            DBG_PRINT("Deleting %d row\n", i);
            shift_left(matrix->matrix, matrix->row, i);
        }
        else
            i++;
    }

    matrix->row -= deleted;
    matrix->alloc_row -= deleted;
    matrix->matrix = realloc(matrix->matrix, matrix->row * sizeof(int *));

    return deleted;
}

/*
    1   2   3

    4   5   6

    7   8   9
*/

static int count_around(matrix_t *matrix, int row, int clm)
{
    int count = 0;

    if (row < matrix->row - 1)
    {
        DBG_PUTS("DOWN");
        count += matrix->matrix[row + 1][clm] == -1; // DOWN
    }
    if (clm < matrix->clm - 1)
    {
        DBG_PUTS("RIGHT");
        count += matrix->matrix[row][clm + 1] == -1; // RIGHT
    }
    if (row > 0)
    {
        DBG_PUTS("UP");
        count += matrix->matrix[row - 1][clm] == -1; // UP
    }
    if (clm > 0)
    {   
        DBG_PUTS("LEFT");
        count += matrix->matrix[row][clm - 1] == -1; // LEFT
    }

    if (row > 0 && clm > 0) // LEFT + UP
        count += matrix->matrix[row - 1][clm - 1] == -1;
    if (clm > 0 && row < matrix->row - 1) // DOWN + LEFT
        count += matrix->matrix[row + 1][clm - 1] == -1;
    if (row < matrix->row - 1 && clm < matrix->clm - 1) // DOWN + RIGHT
        count += matrix->matrix[row + 1][clm + 1] == -1;
    if (row > 0 && clm < matrix->clm - 1) // UP + RIGHT
        count += matrix->matrix[row - 1][clm + 1] == -1;

    DBG_PRINT("Counting -1 for (%d, %d) is %d\n", row, clm, count);

    return count;
}

int change_zeroes(matrix_t *matrix)
{
    int changed = 0;
    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->clm; j++)
            if (!matrix->matrix[i][j])
            {
                changed++;
                matrix->matrix[i][j] = count_around(matrix, i, j);
            }
        
    return changed;
}

void print_matrix(matrix_t *matrix)
{
    printf("%d %d\n", matrix->row, matrix->clm);
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->clm; j++)
            printf("%d\t", matrix->matrix[i][j]);
        printf("\n");
    }
}

static int count_unzero(matrix_t *matrix)
{
    int unzero = 0;

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->clm; j++)
            unzero += (matrix->matrix[i][j] != 0);

    return unzero;
}

void print_in_file(FILE *f, matrix_t *matrix)
{
    fprintf(f, "%d %d %d\n", matrix->row, matrix->clm, count_unzero(matrix));

    for (int i = 0; i < matrix->row; i++)
        for (int j = 0; j < matrix->clm; j++)
            if (matrix->matrix[i][j])
                fprintf(f, "%d %d %d\n", i + 1, j + 1, matrix->matrix[i][j]);
}
