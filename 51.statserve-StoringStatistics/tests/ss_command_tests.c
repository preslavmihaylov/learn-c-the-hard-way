#include "minunit.h"
#include <ss_command.h>

char *test_parse()
{
    {
        SS_Command *res = ss_command_parse(NULL);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when given NULL");
    }

    {
        bstring str = bfromcstr("create /abc");
        bstring expectedParm1 = bfromcstr("/abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Create, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong key after create");
        mu_assert(res->parm2 == NULL, "Param 2 is expected to not be set after create");

        bdestroy(str);
        bdestroy(expectedParm1);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("create");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when create command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("create /aaaa /aaaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when create command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("mean abc");
        bstring expectedParm1 = bfromcstr("abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Mean, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong key after mean");
        mu_assert(res->parm2 == NULL, "Param 2 is expected to not be set after mean");

        bdestroy(str);
        bdestroy(expectedParm1);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("mean");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when mean command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("mean aaaa aaaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when mean command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("dump abc");
        bstring expectedParm1 = bfromcstr("abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Dump, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong key after dump");
        mu_assert(res->parm2 == NULL, "Param 2 is expected to not be set after dump");

        bdestroy(str);
        bdestroy(expectedParm1);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("dump");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when dump command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("dump aaaa aaaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when dump command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("sample abc 123");
        bstring expectedParm1 = bfromcstr("abc");
        bstring expectedParm2 = bfromcstr("123");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Sample, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong param 1 after dump");
        mu_assert(bstrcmp(res->parm2, expectedParm2) == 0, "Wrong param 2 after dump");

        bdestroy(str);
        bdestroy(expectedParm1);
        bdestroy(expectedParm2);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("sample");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when sample command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("sample aaaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when sample command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("sample aaaa aaa aa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when sample command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("sample aaaa aaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when sample command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("exit");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Exit, "Wrong cmd type");
        mu_assert(res->parm1 == NULL, "Param 1 is expected to not be set after exit");
        mu_assert(res->parm2 == NULL, "Param 2 is expected to not be set after exit");

        bdestroy(str);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("exit aaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when exit command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("store abc");
        bstring expectedParm1 = bfromcstr("abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Store, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong param 1 after store");

        bdestroy(str);
        bdestroy(expectedParm1);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("store aaa aaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when store command is invalid");

        bdestroy(str);
    }

    {
        bstring str = bfromcstr("load abc");
        bstring expectedParm1 = bfromcstr("abc");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res != NULL, "ss_command_parse unexpectedly returned NULL");
        mu_assert(res->cmdType == SS_CmdType_Load, "Wrong cmd type");
        mu_assert(bstrcmp(res->parm1, expectedParm1) == 0, "Wrong param 1 after load");

        bdestroy(str);
        bdestroy(expectedParm1);
        ss_command_destroy(res);
    }

    {
        bstring str = bfromcstr("load aaa aaa");

        SS_Command *res = ss_command_parse(str);
        mu_assert(res == NULL, "ss_command_parse expected to return NULL when load command is invalid");

        bdestroy(str);
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_parse);

    return NULL;
}

RUN_TESTS(all_tests);
