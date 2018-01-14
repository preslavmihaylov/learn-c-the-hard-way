#include "minunit.h"
#include <lcthw/hashmap.h>
//#include <assert.h>
#include <lcthw/bstrlib.h>

Hashmap *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static bool traverse_good_cb(HashmapNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;

	return true;
}

static bool traverse_fail_cb(HashmapNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;

	if (traverse_called == 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

char *test_create()
{
	map = Hashmap_create(NULL, NULL);
	mu_assert(map != NULL, "Failed to create map.");

	return NULL;
}

char *test_destroy()
{
	Hashmap_destroy(map);

	return NULL;
}

char *test_get_set()
{
	bool rc;
	bstring result;

	rc = Hashmap_set(map, &test1, &expect1);
	mu_assert(rc == true, "Failed to set test1");

	result = Hashmap_get(map, &test1);
	mu_assert(result == &expect1, "Wrong value for test1");

	rc = Hashmap_set(map, &test2, &expect2);
	mu_assert(rc == true, "Failed to set test2");

	result = Hashmap_get(map, &test2);
	mu_assert(result == &expect2, "Wrong value for test2");

	rc = Hashmap_set(map, &test3, &expect3);
	mu_assert(rc == true, "Failed to set test3");

	result = Hashmap_get(map, &test3);
	mu_assert(result == &expect3, "Wrong value for test3");

	return NULL;
}

char *test_traverse()
{
	bool rc;

	rc = Hashmap_traverse(map, traverse_good_cb);
	mu_assert(rc == true, "Failed to traverse, good case");
	mu_assert(traverse_called == 3, "Wrong count traverse, good case");

	traverse_called = 0;
	rc = Hashmap_traverse(map, traverse_fail_cb);
	mu_assert(rc == false, "Failed to traverse, fail case");
	mu_assert(traverse_called == 2, "Wrong count traverse, fail case");

	return NULL;
}

char *test_delete()
{
	bstring deleted;
	bstring result;

	deleted = (bstring)Hashmap_delete(map, &test1);
	mu_assert(deleted != NULL, "Got NULL on delete element 1");
	mu_assert(deleted == &expect1, "Should get element 1 on delete");

	result = Hashmap_get(map, &test1);
	mu_assert(result == NULL,
			  "Should get NULL when getting deleted element 1");

	deleted = (bstring)Hashmap_delete(map, &test2);
	mu_assert(deleted != NULL, "Got NULL on delete element 2");
	mu_assert(deleted == &expect2, "Should get element 2 on delete");

	result = Hashmap_get(map, &test2);
	mu_assert(result == NULL,
			  "Should get NULL when getting deleted element 2");

	deleted = (bstring)Hashmap_delete(map, &test3);
	mu_assert(deleted != NULL, "Got NULL on delete element 3");
	mu_assert(deleted == &expect3, "Should get element 3 on delete");

	result = Hashmap_get(map, &test3);
	mu_assert(result == NULL,
			  "Should get NULL when getting deleted element 3");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_get_set);
	mu_run_test(test_traverse);
	mu_run_test(test_delete);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);
