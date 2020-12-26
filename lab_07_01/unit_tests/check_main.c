#include <check.h>
#include <stdio.h>
#include "check_file.h"
#include "check_funcs.h"

int main(void)
{
    Suite *s = read_suite();

    SRunner *runner = srunner_create(s);

    srunner_add_suite(runner, write_suite());
    srunner_add_suite(runner, file_len_suite());
    srunner_add_suite(runner, key_suite());
    srunner_add_suite(runner, min_max_suite());
    srunner_add_suite(runner, sort_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int res = srunner_ntests_failed(runner);
    
    srunner_free(runner);

    // printf("Res: %d\n", res);
    return res > 0;
}
