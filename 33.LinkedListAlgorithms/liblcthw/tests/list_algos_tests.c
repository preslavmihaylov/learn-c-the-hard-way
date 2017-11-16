#include "minunit.h"
//#include <lcthw/list_algos.h>
#include <lcthw/list.h>
#include <assert.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5

List *create_words()
{
	int i = 0;

	List *words = List_create();
	
	for (i = 0; i < NUM_VALUES; i++) 
	{
		List_push(words, values[i]);
	}

	return words;
}

int is_sorted(List *words)
{
	LIST_FOREACH(curr, words) {
		if (curr->next && strcmp(curr->value, curr->next->value) > 0)
		{
			debug("%s %s", (char *)curr->value, (char *)curr->next->value);
			return 0;
		}
	}

	return 1;
}

char *test_bubble_sort()
{
	List *words = create_words();
	(void)words;

	return NULL;
}

char *test_merge_sort()
{
	List *words = create_words();
	(void)words;

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_bubble_sort);
	mu_run_test(test_merge_sort);

	return NULL;
}

RUN_TESTS(all_tests);
