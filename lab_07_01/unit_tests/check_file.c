#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "error.h"
#include "check_file.h"

START_TEST(read_empty_file_check)
{
    FILE *f = fopen("./unit_tests/empty_test.txt", "r");

    int res = read_file(f, NULL, NULL);

    ck_assert_int_eq(res, EMPTY_FILE);
}
END_TEST


START_TEST(read_bad_file_check)
{
    FILE *f = fopen("./unit_tests/bad_file_1.txt", "r");

    int res = read_file(f, NULL, NULL);

    ck_assert_int_eq(res, BAD_FILE);
}
END_TEST

START_TEST(read_crc_file_check)
{
    FILE *f = fopen("./unit_tests/correct_file_1.txt", "r");

    int *a = NULL;
    int *b = NULL;

    int res = read_file(f, &a, &b);

    ck_assert_int_eq(res, NO_ERROR);
    free(a);
}
END_TEST

Suite *read_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("Read file");
    
    tc_neg = tcase_create("negatives");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_neg, read_empty_file_check);
    tcase_add_test(tc_neg, read_bad_file_check);

    tcase_add_test(tc_pos, read_crc_file_check);

    suite_add_tcase(s, tc_neg);
    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(write_file_bad_file)
{
    FILE *f = fopen("./unit_tests/correct_file_1.txt", "r");
    
    int a[] = {1, 2, 3};

    int res = write_file(f, a, a + 2);

    ck_assert_int_eq(res, NO_ERROR);
}
END_TEST

Suite *write_suite(void)
{
    Suite *s;
    TCase *tc_neg;

    s = suite_create("Write file");
    
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, write_file_bad_file);


    suite_add_tcase(s, tc_neg);

    return s;
}


START_TEST(get_file_len_empty)
{
    FILE *f = fopen("./unit_tests/empty_test.txt", "r");
    
    int len;
    int res = get_file_len(f, &len);

    ck_assert_int_eq(res, NO_ERROR);
    ck_assert_int_eq(len, 0);
}
END_TEST

START_TEST(get_file_len_bad_file)
{
    FILE *f = fopen("./unit_tests/bad_file_1.txt", "r");
    
    int len;
    int res = get_file_len(f, &len);

    ck_assert_int_eq(res, BAD_FILE);
}
END_TEST

START_TEST(get_file_len_crc)
{
    FILE *f = fopen("./unit_tests/correct_file_1.txt", "r");

    int len;
    int res = get_file_len(f, &len);

    ck_assert_int_eq(res, NO_ERROR);
    ck_assert_int_eq(len, 4);
}
END_TEST

Suite *file_len_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("File len");
    
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, get_file_len_bad_file);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, get_file_len_empty);
    tcase_add_test(tc_pos, get_file_len_crc);

    suite_add_tcase(s, tc_pos);

    return s;
}