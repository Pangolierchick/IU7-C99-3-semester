/*
    Удаление:
    Удаление с минимальным элементом
    Который был встречен последним
    При обходе по столбцам

    Добавление:
    Сначала строки, потом столбцы
    Среднее геометрическое столбцов
    Добавлять минимумы по строкам

*/

#include <stdio.h>
#include "matrix_public.h"
#include "io.h"
#include "logger.h"
#include "my_error.h"

#define CLEAN_MATRIXES()        clean_matrix(matrix1);  \
                                clean_matrix(matrix2);  \
                                clean_matrix(mult_res); \

#if DEBUG

int res;

void end_callback(void)
{
    DBG_PRINT("Exit code: %d\n", res);
}

#endif

int main(void)
{
#if DEBUG
    atexit(end_callback);
#else
    int res;
#endif

    matrix_t *matrix1 = NULL;
    matrix_t *matrix2 = NULL;
    matrix_t *mult_res = NULL;

    res = input_matrix(&matrix1);
    
    if (res)
    {
        CLEAN_MATRIXES();
        return res;
    }
    
    res = input_matrix(&matrix2);

    if (res)
    {
        CLEAN_MATRIXES();
        return res;
    }


    matrix1 = squarize(matrix1);
    matrix2 = squarize(matrix2);

#if DEBUG
    print_matrix(matrix1);
    print_matrix(matrix2);
#endif

    int new_size = MAX(matrix1->row, matrix2->row);

    matrix1 = enlarge(matrix1, new_size);

    if (matrix1 == NULL)
    {
        CLEAN_MATRIXES();
        return matrix_errno;
    }

    matrix2 = enlarge(matrix2, new_size);

    if (matrix2 == NULL)
    {
        CLEAN_MATRIXES();
        return matrix_errno;
    }

#if DEBUG  
    print_matrix(matrix1);
    print_matrix(matrix2);
#endif

    res = multiplication_task(matrix1, matrix2, &mult_res);

    if (res)
    {
        CLEAN_MATRIXES();
        return res;
    }

    print_matrix(mult_res);

    CLEAN_MATRIXES();

    return NO_ERROR;
}
