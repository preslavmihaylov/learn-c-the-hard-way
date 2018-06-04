#include "minunit.h"
#include <lcthw/tstree.h>


char *test_insert()
{
    return NULL;
}

char *test_search_exact()
{
    return NULL;
}

char *test_search_prefix()
{
    return NULL;
}

char *test_traverse()
{
    return NULL;
}

char *test_destroy()
{
    return NULL; 
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_insert);
    mu_run_test(test_search_exact);
    mu_run_test(test_search_prefix);
    mu_run_test(test_traverse);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
