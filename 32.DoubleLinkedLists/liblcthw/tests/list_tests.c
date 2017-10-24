#include "minunit.h"
#include <list.h>
#include <assert.h>

//static List *list = NULL;

char *test_list_create()
{
	return NULL;
}

char *test_list_destroy()
{
	return NULL;
}

char *test_list_clear()
{
	return NULL;
}

char *test_list_clear_destroy()
{
	return NULL;
}

char *test_list_count()
{
	return NULL;
}

char *test_list_first()
{
	return NULL;
}

char *test_list_last()
{
	return NULL;
}

char *test_list_push()
{
	return NULL;
}

char *test_list_pop()
{
	return NULL;
}

char *test_list_unshift()
{
	return NULL;
}

char *test_list_shift()
{
	return NULL;
}

char *test_list_remove()
{
	return NULL;
}


char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_list_create);
    mu_run_test(test_list_destroy);
    mu_run_test(test_list_clear);
    mu_run_test(test_list_clear_destroy);
    mu_run_test(test_list_count);
    mu_run_test(test_list_first);
    mu_run_test(test_list_last);
    mu_run_test(test_list_push);
    mu_run_test(test_list_pop);
    mu_run_test(test_list_unshift);
    mu_run_test(test_list_shift);
    mu_run_test(test_list_remove);

    return NULL;
}

RUN_TESTS(all_tests);
