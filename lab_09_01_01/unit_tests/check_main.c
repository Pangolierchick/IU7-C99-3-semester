#include <check.h>

Suite *safe_atoi_check(void);

int main(void)
{
    Suite *s = safe_atoi_check();

    SRunner *runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);

    int res = srunner_ntests_failed(runner);

    srunner_free(runner);

    return res > 0;
}
