#include <check.h>
#include <stdio.h>

Suite *list_push(void);
Suite *list_find(void);
Suite *list_insert(void);
Suite *list_sort(void);

int main(void)
{
    Suite *s = list_push();

    SRunner *runner = srunner_create(s);

    srunner_add_suite(runner, list_find());
    srunner_add_suite(runner, list_insert());
    srunner_add_suite(runner, list_sort());

    srunner_run_all(runner, CK_VERBOSE);

    int res = srunner_ntests_failed(runner);

    srunner_free(runner);

    return res > 0;
}
