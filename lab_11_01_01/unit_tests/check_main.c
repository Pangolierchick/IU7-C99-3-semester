#include <check.h>
#include <stdio.h>

Suite *snprintf_test(void);

int main(void)
{
    Suite *s = snprintf_test();

    SRunner *runner = srunner_create(s);

    // srunner_add_suite(runner, snprintf_test());

    srunner_run_all(runner, CK_VERBOSE);

    int res = srunner_ntests_failed(runner);
    
    srunner_free(runner);

    // printf("Res: %d\n", res);
    return res > 0;
}
