#include <check.h>
#include "../inc/funcs.h"

START_TEST(safe_atoi_1)
{
    char arr[] = "123";
    int res;
    int val;

    res = safe_atoi(arr, &val);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(val, 123);
}
END_TEST

START_TEST(safe_atoi_2)
{
    char arr[] = "1a23";
    int res;
    int val;

    res = safe_atoi(arr, &val);

    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(safe_atoi_3)
{
    char arr[] = "a";
    int res;
    int val;

    res = safe_atoi(arr, &val);

    ck_assert_int_eq(res, 1);
}
END_TEST

Suite *safe_atoi_check(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("Safe atoi");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, safe_atoi_1);
    suite_add_tcase(s, tc_pos);

    tcase_add_test(tc_neg, safe_atoi_2);
    tcase_add_test(tc_neg, safe_atoi_3);

    suite_add_tcase(s, tc_neg);

    return s;
}
