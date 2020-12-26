#include <check.h>
#include <string.h>
#include "matrix_public.h"
#include "matrix_private.h"


static int cmp_matrixes(matrix_t *m1, matrix_t *m2)
{
    if (m1->row != m2->row)
        return m1->row > m2->row;

    if (m1->clm != m2->clm)
        return m1->clm > m2->clm;

    for (int i = 0; i < m1->alloc_row; i++)
        for (int j = 0; j < m1->alloc_clm; j++)
            if (m1->matrix[i][j] != m2->matrix[i][j])
                return m1->matrix[i][j] - m2->matrix[i][j];
    
    return 0;
}

START_TEST(matrix_mult_1)
{
    matrix_t *m1 = init_matrix(2, 2);

    m1->clm = 2;
    m1->row = 2;

    m1->matrix[0][0] = 1;
    m1->matrix[0][1] = 2;
    m1->matrix[1][0] = 3;
    m1->matrix[1][1] = 4;

    matrix_t *m2 = init_matrix(2, 2);

    m2->clm = 2;
    m2->row = 2;

    m2->matrix[0][0] = 1;
    m2->matrix[0][1] = 2;
    m2->matrix[1][0] = 3;
    m2->matrix[1][1] = 4;

    matrix_t *m3 = init_matrix(2, 2);

    matrix_t *res = init_matrix(2, 2);

    res->clm = 2;
    res->row = 2;

    res->matrix[0][0] = 7;
    res->matrix[0][1] = 10;
    res->matrix[1][0] = 15;
    res->matrix[1][1] = 22;

    multiplication(m1, m2, m3);

    int cmp_res = cmp_matrixes(m3, res);

    ck_assert_int_eq(cmp_res, 0);

    clean_matrix(m1);
    clean_matrix(m2);
    clean_matrix(m3);
    clean_matrix(res);
}
END_TEST

START_TEST(matrix_mult_2)
{
    matrix_t *m1 = init_matrix(2, 2);

    m1->clm = 2;
    m1->row = 2;

    m1->matrix[0][0] = 1;
    m1->matrix[0][1] = 0;
    m1->matrix[1][0] = 3;
    m1->matrix[1][1] = 6;

    matrix_t *m2 = init_matrix(2, 2);

    m2->clm = 2;
    m2->row = 2;

    m2->matrix[0][0] = 0;
    m2->matrix[0][1] = 0;
    m2->matrix[1][0] = 6;
    m2->matrix[1][1] = 9;

    matrix_t *m3 = init_matrix(2, 2);

    matrix_t *res = init_matrix(2, 2);

    res->clm = 2;
    res->row = 2;

    res->matrix[0][0] = 0;
    res->matrix[0][1] = 0;
    res->matrix[1][0] = 36;
    res->matrix[1][1] = 54;

    multiplication(m1, m2, m3);

    int cmp_res = cmp_matrixes(m3, res);

    ck_assert_int_eq(cmp_res, 0);

    clean_matrix(m1);
    clean_matrix(m2);
    clean_matrix(m3);
    clean_matrix(res);
}
END_TEST

Suite *matrix_mult(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Matrix mult");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, matrix_mult_1);
    tcase_add_test(tc_pos, matrix_mult_2);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(geom_mean_1)
{
    matrix_t *m1 = init_matrix(2, 2);

    m1->row = 2;
    m1->clm = 2;

    m1->matrix[0][0] = 1;
    m1->matrix[0][1] = 0;
    m1->matrix[1][0] = 3;
    m1->matrix[1][1] = 9;

    int res = elm_geom_mean(m1, 1);

    clean_matrix(m1);

    ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(geom_mean_2)
{
    matrix_t *m1 = init_matrix(3, 2);

    m1->row = 3;
    m1->clm = 2;

    m1->matrix[0][0] = 1;
    m1->matrix[1][0] = 1;
    m1->matrix[2][0] = 1;

    m1->matrix[0][1] = 3;
    m1->matrix[1][1] = 9;
    m1->matrix[2][1] = 12;

    int res = elm_geom_mean(m1, 1);

    clean_matrix(m1);

    ck_assert_int_eq(res, 6);
}
END_TEST

Suite *geom_mean(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Geom mean");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, geom_mean_1);
    tcase_add_test(tc_pos, geom_mean_2);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(enlarge_1)
{
    matrix_t *m1 = init_matrix(2, 2);

    m1->row = 2;
    m1->clm = 2;

    m1->matrix[0][0] = 1;
    m1->matrix[1][0] = 1;

    m1->matrix[0][1] = 3;
    m1->matrix[1][1] = 9;

    m1 = enlarge(m1, 3);

    ck_assert_int_ne(m1 == NULL, 1);
    ck_assert_int_eq(m1->row, 3);
    ck_assert_int_eq(m1->clm, 3);

    clean_matrix(m1);
}
END_TEST

Suite *enlarge_test(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("enlarge");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, enlarge_1);

    suite_add_tcase(s, tc_pos);

    return s;
}
