#include "minunit.h"
#include <list.h>
#include <assert.h>

char *test_list_create()
{
    List *list = List_create();
    mu_assert(list != NULL, "List_create didn't create list");

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
    void *firstElement = (void *)5;
    void *secondElement = (void *)6;

    List *list = List_create();

    List_push(list, firstElement);
    
    mu_assert(list->count == 1, "Count not incremented upon push");
    
    mu_assert(list->first->value == firstElement, 
            "list_push 1 did not modify first element");
    mu_assert(list->last->value == firstElement, 
            "list_push 1 did not modify last element");

    List_push(list, secondElement);

    mu_assert(list->first->value == firstElement, 
            "list_push 2 modified first element");
    mu_assert(list->last->value == secondElement, 
            "list_push 2 did not modify second element");
    // TODO: FINISH

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

char *test_list_clear_destroy()
{
	return NULL;
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_list_create);
    mu_run_test(test_list_count);
    mu_run_test(test_list_first);
    mu_run_test(test_list_last);
    mu_run_test(test_list_push);
    mu_run_test(test_list_pop);
    mu_run_test(test_list_unshift);
    mu_run_test(test_list_shift);
    mu_run_test(test_list_remove);
    mu_run_test(test_list_clear_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
