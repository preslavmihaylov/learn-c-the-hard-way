#include "minunit.h"
#include <ss_command.h>

char *test_create()
{
    SS_Command *cmd = ss_command_create();
    mu_assert(cmd != NULL, "ss_command_create returned NULL");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);

    return NULL;
}

RUN_TESTS(all_tests);
