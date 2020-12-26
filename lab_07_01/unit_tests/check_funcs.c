#include <check.h>
#include <string.h>
#include <stdlib.h>
#include "check_funcs.h"
#include "funcs.h"
#include "error.h"

START_TEST(correct_1_array_min_max)
{
    int array[] = { 1, 2, 3, 4 };
    array_elem_t min;
    array_elem_t max;

    array_min_max(array, array + 4, &min, &max);

    ck_assert_int_eq(min.val, 1);
    ck_assert_int_eq(max.val, 4);
    
    ck_assert_int_eq(min.ind, 0);
    ck_assert_int_eq(max.ind, 3);
}
END_TEST

START_TEST(correct_2_array_min_max)
{
    int array[] = { 4, 2, 10, 0, 1 };
    array_elem_t min;
    array_elem_t max;

    array_min_max(array, array + 5, &min, &max);

    ck_assert_int_eq(min.val, 0);
    ck_assert_int_eq(max.val, 10);

    ck_assert_int_eq(min.ind, 3);
    ck_assert_int_eq(max.ind, 2);
}
END_TEST

START_TEST(correct_3_array_min_max)
{
    int array[] = { 0, 0, 0, 0, 0 };
    array_elem_t min;
    array_elem_t max;

    array_min_max(array, array + 5, &min, &max);

    ck_assert_int_eq(min.val, 0);
    ck_assert_int_eq(max.val, 0);

    ck_assert_int_eq(min.ind, 0);
    ck_assert_int_eq(max.ind, 0);
}
END_TEST

Suite *min_max_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Array min max");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, correct_1_array_min_max);
    tcase_add_test(tc_pos, correct_2_array_min_max);
    tcase_add_test(tc_pos, correct_3_array_min_max);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(key_1_correct)
{
    int array[] = { 1, 2, 3, 4 };
    int *new_array_b = NULL;
    int *new_array_e = NULL;
    const int res_arr[] = { 2, 3 };

    int res = key(array, array + 4, &new_array_b, &new_array_e);
    int cmp_res = memcmp(res_arr, new_array_b, 2);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(cmp_res, 0);

    free(new_array_b);
}
END_TEST

START_TEST(key_2_correct)
{
    int array[] = { 1, 2, 3, 4, 5, 6 };
    int *new_array_b = NULL;
    int *new_array_e = NULL;
    const int res_arr[] = { 2, 3, 4, 5 };

    int res = key(array, array + 6, &new_array_b, &new_array_e);
    int cmp_res = memcmp(res_arr, new_array_b, 4);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(cmp_res, 0);

    free(new_array_b);
}
END_TEST

START_TEST(key_empty_1)
{
    int array[] = { 4, 4, 4, 4 };
    int *new_array_b = NULL;
    int *new_array_e = NULL;

    int res = key(array, array + 4, &new_array_b, &new_array_e);

    ck_assert_int_eq(res, EQUAL_ARRAY_FILTER_FAULT);
}
END_TEST

START_TEST(key_empty_2)
{
    int array[] = { 4, 4 };
    int *new_array_b = NULL;
    int *new_array_e = NULL;

    int res = key(array, array + 2, &new_array_b, &new_array_e);

    ck_assert_int_eq(res, EQUAL_ARRAY_FILTER_FAULT);
}
END_TEST

START_TEST(key_empty_3)
{
    int array[] = { 4 };
    int *new_array_b = NULL;
    int *new_array_e = NULL;

    int res = key(array, array + 2, &new_array_b, &new_array_e);

    ck_assert_int_eq(res, EQUAL_ARRAY_FILTER_FAULT);
}
END_TEST

START_TEST(key_null)
{
    int res = key(NULL, NULL, NULL, NULL);

    ck_assert_int_eq(res, NULL_POINTER);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("Key");
    
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, key_empty_1);
    tcase_add_test(tc_neg, key_empty_2);
    tcase_add_test(tc_neg, key_empty_3);
    tcase_add_test(tc_neg, key_null);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, key_1_correct);
    tcase_add_test(tc_pos, key_2_correct);

    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(mysort_int)
{
    int array[] = { 3, 4, 5, 1, 3, 9, 12, 15 };
    const int res_array[] = { 1, 3, 3, 4, 5, 9, 12, 15 };
    mysort(array, 8, sizeof(int), int_cmp);

    ck_assert_int_eq(0, memcmp(array, res_array, 8));
}
END_TEST

int __cmp(const void *a, const void *b)
{
    const char *pa = a;
    const char *pb = b;

    return strcmp(pa, pb);
}

START_TEST(mysort_str)
{
    char array[][25] = { "bbb", "ccc", "aaa", "vvv", "a" };
    const char res_array[][25] = { "a", "aaa", "bbb", "ccc", "vvv" };
    mysort((void *) array, 5, sizeof(char) * 25, __cmp);

    ck_assert_int_eq(0, memcmp(array, res_array, 5));
}
END_TEST

START_TEST(mysort_null_base)
{
    mysort(NULL, 2, 3, int_cmp);
    ck_assert_int_eq(NULL_BASE, mysort_errno);
}
END_TEST

START_TEST(mysort_null_cmp)
{
    int a[] = { 1, 2, 3 };
    mysort(a, 3, sizeof(int), NULL);
    ck_assert_int_eq(NULL_CMP, mysort_errno);
}
END_TEST

START_TEST(my_sort_bad_nel)
{
    int a[] = { 1, 2, 3 };
    mysort(a, 0, sizeof(int), int_cmp);
    ck_assert_int_eq(BAD_NEL, mysort_errno);
}
END_TEST

START_TEST(my_sort_bad_width)
{
    int a[] = { 1, 2, 3 };
    mysort(a, 3, 0, int_cmp);
    ck_assert_int_eq(BAD_WIDTH, mysort_errno);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("Sort");
    
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, mysort_null_base);
    tcase_add_test(tc_neg, mysort_null_cmp);
    tcase_add_test(tc_neg, my_sort_bad_width);
    tcase_add_test(tc_neg, my_sort_bad_nel);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, mysort_int);
    tcase_add_test(tc_pos, mysort_str);

    suite_add_tcase(s, tc_pos);

    return s;
}