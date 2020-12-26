#include <stdio.h>
#include "io.h"
#include "my_error.h"
#include "logger.h"

int input_matrix(matrix_t **matrix)
{
    DBG_PUTS("-------Inputting matrix-------");

    printf("Input number of rows: ");

    int x;
    int y;

    if (scanf("%d", &y) != 1)
        return BAD_ROW;

    if (y <= 0)
        return NEGATIVE_ROW_CLM;

    DBG_PRINT("number of rows %d\n", y);

    printf("Input number of columns: ");

    if (scanf("%d", &x) != 1)
        return BAD_CLM;

    if (x <= 0)
        return NEGATIVE_ROW_CLM;

    DBG_PRINT("number of clms %d\n", x);

    matrix_t *temp_matrix = init_matrix(y, x);

    if (temp_matrix == NULL)
        return ALLOC_FAILED;

    printf("Input matrix elems: ");

    for (int row = 0; row < y; row++)
    {
        for (int clm = 0; clm < x; clm++)
        {
            if (scanf("%d", &(temp_matrix->matrix[row][clm])) != 1)
            {
                *matrix = temp_matrix;
                return BAD_MATRIX_ELEM;
            }
        }
    }

    temp_matrix->clm = x;
    temp_matrix->row = y;

    *matrix = temp_matrix;

    DBG_PUTS("--------------------");

    return NO_ERROR;
}

void print_matrix(const matrix_t *matrix)
{
#if DEBUG
    printf("row %d\tclm %d\n", matrix->row, matrix->clm);
#endif
    for (int row = 0; row < matrix->row; row++)
    {
        for (int clm = 0; clm < matrix->clm; clm++)
            printf("\t%d", matrix->matrix[row][clm]);
        printf("\n");
    }
}
