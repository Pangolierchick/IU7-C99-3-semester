#include <check.h>
#include <stdio.h>

Suite *matrix_mult(void);
Suite *geom_mean(void);
Suite *enlarge_test(void);

int main(void)
{
    Suite *s = matrix_mult();

    SRunner *runner = srunner_create(s);

    srunner_add_suite(runner, geom_mean());
    srunner_add_suite(runner, enlarge_test());

    srunner_run_all(runner, CK_VERBOSE);

    int res = srunner_ntests_failed(runner);

    srunner_free(runner);

    return res > 0;
}
