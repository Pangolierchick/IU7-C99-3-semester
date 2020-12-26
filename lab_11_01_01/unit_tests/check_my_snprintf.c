#include <check.h>
#include <stdio.h>
#include "my_snprintf.h"

START_TEST(my_snprintf_1)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %d apples\n";

    char my_buff[10];
    char std_buff[10];

    int num = 10;

    my_res = my_snprintf(my_buff, 10, msg, num);
    std_res = snprintf(std_buff, 10, msg, num);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


START_TEST(my_snprintf_2)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %d apples\n";

    char my_buff[5];
    char std_buff[5];

    int num = 10;

    my_res = my_snprintf(my_buff, 5, msg, num);
    std_res = snprintf(std_buff, 5, msg, num);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


START_TEST(my_snprintf_3)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %x apples\n";

    char my_buff[15];
    char std_buff[15];

    int num = 10;

    my_res = my_snprintf(my_buff, 15, msg, num);
    std_res = snprintf(std_buff, 15, msg, num);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


START_TEST(my_snprintf_4)
{
    int my_res;
    int std_res;

    const char msg[] = "I have apples\n";

    char my_buff[20];
    char std_buff[20];

    my_res = my_snprintf(my_buff, 20, msg);
    std_res = snprintf(std_buff, 20, msg);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_5)
{
    int my_res;
    int std_res;

    const char msg[] = "I have apples\n";

    char my_buff[20] = { 0 };
    char std_buff[20] = { 0 };

    my_res = my_snprintf(my_buff, 0, msg);
    std_res = snprintf(std_buff, 0, msg);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


START_TEST(my_snprintf_6)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %s apples\n";

    char my_buff[20] = { 0 };
    char std_buff[20] = { 0 };

    const char word[] = "ten";

    my_res = my_snprintf(my_buff, 20, msg, word);
    std_res = snprintf(std_buff, 20, msg, word);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


START_TEST(my_snprintf_7)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %s apples\n";

    char my_buff[20] = { 0 };
    char std_buff[20] = { 0 };

    const char word[] = "ten";

    my_res = my_snprintf(my_buff, 8, msg, word);
    std_res = snprintf(std_buff, 8, msg, word);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_8)
{
    int my_res;
    int std_res;

    const char msg[] = "I have %s apples %s\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    const char word[] = "ten";
    const char word2[] = "in bucket";

    my_res = my_snprintf(my_buff, 40, msg, word, word2);
    std_res = snprintf(std_buff, 40, msg, word, word2);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_9)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%s%x%c\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(my_buff, 40, msg, 123, "123", 123, '2');
    std_res = snprintf(std_buff, 40, msg, 123, "123", 123, '2');

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_10)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%x\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(my_buff, 40, msg, -123, -123);
    std_res = snprintf(std_buff, 40, msg, -123, -123);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_11)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%x\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(my_buff, 40, msg, -123, 0);
    std_res = snprintf(std_buff, 40, msg, -123, 0);

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_12)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%s%x%c\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(my_buff, 5, msg, 123, "123", 123, '2');
    std_res = snprintf(std_buff, 5, msg, 123, "123", 123, '2');

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST

START_TEST(my_snprintf_13)
{
    int my_res;
    int std_res;

    const char msg[] = "%d%s%x%c\n";

    char my_buff[40] = { 0 };
    char std_buff[40] = { 0 };

    my_res = my_snprintf(NULL, 0, msg, 123, "123", 123, '2');
    std_res = snprintf(NULL, 0, msg, 123, "123", 123, '2');

    ck_assert_int_eq(my_res, std_res);
    ck_assert_str_eq(my_buff, std_buff);
}
END_TEST


Suite *snprintf_test(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("snprintf test");

    tc = tcase_create("tests");

    tcase_add_test(tc, my_snprintf_1);
    tcase_add_test(tc, my_snprintf_2);
    tcase_add_test(tc, my_snprintf_3);
    tcase_add_test(tc, my_snprintf_4);
    tcase_add_test(tc, my_snprintf_5);
    tcase_add_test(tc, my_snprintf_6);
    tcase_add_test(tc, my_snprintf_7);
    tcase_add_test(tc, my_snprintf_8);
    tcase_add_test(tc, my_snprintf_9);
    tcase_add_test(tc, my_snprintf_10);
    tcase_add_test(tc, my_snprintf_11);
    tcase_add_test(tc, my_snprintf_12);
    tcase_add_test(tc, my_snprintf_13);

    suite_add_tcase(s, tc);

    return s;
}
