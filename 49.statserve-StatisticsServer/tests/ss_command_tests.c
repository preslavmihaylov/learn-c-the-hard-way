#include "minunit.h"
#include <ss_command.h>

char *test_create()
{
    SS_Command *cmd = ss_command_create();
    mu_assert(cmd != NULL, "ss_command_create returned NULL");

    return NULL;
}

char *test_parse()
{
    bstring str = bfromcstr("");

    {
        SS_Command *res = ss_command_parse(NULL);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when given NULL");
    }

    {
        bstring str = bfromcstr("create abc");
        bstring expectedKey = bfromcstr("abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Create, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedKey) == 0, "Wrong key after create");
        mu_assert(res->parm2 == NULL, "Param 2 is expected to not be set after create");
    }

    bdestroy(str);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_parse);

    return NULL;
}

RUN_TESTS(all_tests);
