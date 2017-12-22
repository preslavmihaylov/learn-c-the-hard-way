#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>

BSTree *tree = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(BSTNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;
	return 0;
}

static int traverse_fail_cb(BSTNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;

	if (traverse_called == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

char *test_create()
{
	tree = BSTree_create(NULL);
	mu_assert(tree != NULL, "Failed to create tree");

	return NULL;
}

char *test_destroy()
{
	BSTree_destroy(tree);

	return NULL;
}

char *test_get_set()
{
	int rc;
	bstring result;

	rc = BSTree_set(tree, &test1, &expect1);
	mu_assert(rc == 0, "Failed to set &test1");
	result = BSTree_get(tree, &test1);
	mu_assert(result == &expect1, "Wrong value for test 1");

	rc = BSTree_set(tree, &test2, &expect2);
	mu_assert(rc == 0, "Failed to set &test2");
	result = BSTree_get(tree, &test2);
	mu_assert(result == &expect2, "Wrong value for test 2");

	rc = BSTree_set(tree, &test3, &expect3);
	mu_assert(rc == 0, "Failed to set &test3");
	result = BSTree_get(tree, &test3);
	mu_assert(result == &expect3, "Wrong value for test 3");

	return NULL;
}

char *test_traverse()
{
	int rc;

	rc = BSTree_traverse(tree, traverse_good_cb);
	mu_assert(rc == 0, "Failed to traverse");
	mu_assert(traverse_called == 3, "Wrong count traverse");

	traverse_called = 0;
	rc = BSTree_traverse(tree, traverse_fail_cb);
	mu_assert(rc == 1, "Failed to traverse");
	mu_assert(traverse_called == 2, "Wrong count traverse for fail case");

	return NULL;
}

char *test_delete()
{
	bstring deleted;
	bstring result;

	deleted = (bstring)BSTree_delete(tree, &test1);
	mu_assert(deleted != NULL, "Got NULL on delete");
	mu_assert(deleted == &expect1, "Should get test 1 on delete");
	result = BSTree_get(tree, &test1);
	mu_assert(result == NULL, "Should delete");
	deleted = (bstring)BSTree_delete(tree, &test1);
	mu_assert(deleted == NULL, "Should get NULL on delete");

	deleted = (bstring)BSTree_delete(tree, &test2);
	mu_assert(deleted != NULL, "Got NULL on delete");
	mu_assert(deleted == &expect2, "Should get test 2 on delete");
	result = BSTree_get(tree, &test2);
	mu_assert(result == NULL, "Should delete");
	deleted = (bstring)BSTree_delete(tree, &test2);
	mu_assert(deleted == NULL, "Should get NULL on delete");

	deleted = (bstring)BSTree_delete(tree, &test3);
	mu_assert(deleted != NULL, "Got NULL on delete");
	mu_assert(deleted == &expect3, "Should get test 3 on delete");
	result = BSTree_get(tree, &test3);
	mu_assert(result == NULL, "Should delete");
	deleted = (bstring)BSTree_delete(tree, &test3);
	mu_assert(deleted == NULL, "Should get NULL on delete");

	return NULL;
}

char *test_fuzzing()
{
	int i = 0;
	int j = 0;

	BSTree *store = BSTree_create(NULL);
	bstring numbers[100] = { NULL };
	bstring data[100] = { NULL };
	srand(time(NULL));

	for (i = 0; i < 100; ++i)
	{
		int num = rand();
		numbers[i] = bformat("%d", num);
		data[i] = bformat("data %d", num);

		BSTree_set(store, numbers[i], data[i]);
	}

	for (i = 0; i < 100; i++)
	{
		bstring value = BSTree_delete(store, numbers[i]);

		mu_assert(value == data[i], "Failed to delete the right number");
		mu_assert(BSTree_delete(store, numbers[i]) == NULL,
				  "Should get nothing");

		for (j = i + 1; j < 99 - i; j++)
		{
			bstring value = BSTree_get(store, numbers[j]);
			mu_assert(value == data[j],
					  "Failed to get the right number.");
		}

		bdestroy(value);
		bdestroy(numbers[i]);
	}

	BSTree_destroy(store);

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
	mu_run_test(test_fuzzing);

	return NULL;
}

RUN_TESTS(all_tests);
