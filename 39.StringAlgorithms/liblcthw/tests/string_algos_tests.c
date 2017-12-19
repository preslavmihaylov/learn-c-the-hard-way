#include "minunit.h"
#include <lcthw/string_algos.h>
#include <lcthw/bstrlib.h>
#include <time.h>

struct tagbstring IN_STR1 = bsStatic(
		"I have ALPHA beta ALPHA and oranges ALPHA");
struct tagbstring IN_STR2 = bsStatic(
		"ALPHA beta ALPHA and oranges ALPHA");
struct tagbstring IN_STR3 = bsStatic(
		"beta");
struct tagbstring IN_STR4 = bsStatic(
		"gamma beta ALPHA");
struct tagbstring IN_STR5 = bsStatic(
		"bALPHA");
struct tagbstring ALPHA = bsStatic("ALPHA");

const int TEST_TIME = 1;

char *test_find()
{
	mu_assert(String_find(&IN_STR1, &ALPHA) == binstr(&IN_STR1, 0, &ALPHA),
			  "String_find returned wrong index for IN_STR1");
	mu_assert(String_find(&IN_STR2, &ALPHA) == binstr(&IN_STR2, 0, &ALPHA),
			  "String_find returned wrong index for IN_STR2");
	mu_assert(String_find(&IN_STR3, &ALPHA) == binstr(&IN_STR3, 0, &ALPHA),
			  "String_find returned wrong index for IN_STR3");
	mu_assert(String_find(&IN_STR4, &ALPHA) == binstr(&IN_STR4, 0, &ALPHA),
			  "String_find returned wrong index for IN_STR4");
	mu_assert(String_find(&IN_STR5, &ALPHA) == binstr(&IN_STR5, 0, &ALPHA),
			  "String_find returned wrong index for IN_STR5");

	return NULL;
}

char *test_scan()
{
	StringScanner *scan = StringScanner_create(&IN_STR1);
	mu_assert(scan != NULL, "Failed to make the scanner");
	mu_assert(strcmp((char *)scan->text, (char *)bdata(&IN_STR1)) == 0,
			  "Input text was not corrent upon scanner creation");
	mu_assert(scan->textLength == blength(&IN_STR1),
			  "Scanner length was invalid after creation");

	int scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(scan_i == 7, "Failed to find 'ALPHA' with scan first time");

	scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(scan_i == 18, "should find another ALPHA after the first");

	scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(scan_i == 36, "should find another ALPHA after the second");

	mu_assert(StringScanner_scan(scan, &ALPHA) == -1,
			  "shouldn't find text after scan is complete");

	StringScanner_destroy(scan);

	return NULL;
}

char *test_binstr_performance()
{
	int i = 0;
	int found_at = 0;
	unsigned long find_count = 0;
	time_t elapsed = 0;
	time_t start = time(NULL);

	do {
		for (i = 0; i < 1000; i++)
		{
			found_at = binstr(&IN_STR1, 0, &ALPHA);
			mu_assert(found_at != BSTR_ERR, "Failed to find!");
			find_count++;
		}

		elapsed = time(NULL) - start;
	} while(elapsed <= TEST_TIME);

	debug("BINSTR COUNT: %lu, END_TIME: %d, OPS: %f",
		find_count, (int)elapsed, (double)find_count / elapsed);

	return NULL;
}

char *test_find_performance()
{
	int i = 0;
	unsigned long find_count = 0;
	time_t elapsed = 0;
	time_t start = time(NULL);

	do {
		for (i = 0; i < 1000; ++i)
		{
			String_find(&IN_STR1, &ALPHA);
			find_count++;
		}

		elapsed = time(NULL) - start;
	} while (elapsed <= TEST_TIME);

	debug("FIND COUNT: %lu, END TIME: %d, OPS: %f",
		find_count, (int)elapsed, (double)find_count / elapsed);

	return NULL;
}

char *test_scan_performance()
{
	int i = 0;
	int found_at = 0;
	unsigned long find_count = 0;
	time_t elapsed = 0;
	StringScanner *scan = StringScanner_create(&IN_STR1);

	time_t start = time(NULL);

	do {
		for (i = 0; i < 1000; ++i)
		{
			found_at = 0;

			do {
				found_at = StringScanner_scan(scan, &ALPHA);
				find_count++;
			} while (found_at != -1);
		}

		elapsed = time(NULL) - start;
	} while (elapsed <= TEST_TIME);

	debug("SCAN COUNT: %lu, END TIME: %d, OPS: %f",
		find_count, (int)elapsed, (double)find_count / elapsed);

	StringScanner_destroy(scan);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_find);
	mu_run_test(test_scan);

#if 0
	mu_run_test(test_scan_performance);
	mu_run_test(test_find_performance);
	mu_run_test(test_binstr_performance);
#endif

	return NULL;
}

RUN_TESTS(all_tests);
