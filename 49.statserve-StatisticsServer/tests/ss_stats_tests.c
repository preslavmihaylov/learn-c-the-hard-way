#include "minunit.h"

char *test_create()
{
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);

	return NULL;
}

RUN_TESTS(all_tests);
