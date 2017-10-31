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
	List *list = List_create();

	mu_assert(List_count(NULL) == 0, "List_count of NULL did not return 0");

	list->count = 0;
	mu_assert(List_count(list) == 0, "List_count of 0 did not return 0");
	
	list->count = 1;
	mu_assert(List_count(list) == 1, "List_count of 1 did not return 1");
	
	return NULL;
}

char *test_list_first()
{
	List *list = List_create();
	
	mu_assert(List_first(NULL) == NULL, "List_first of NULL did not return NULL");
	
    list->first = NULL;
	mu_assert(List_first(list) == NULL, "List_first of NULL did not return NULL");
	
	list->first = malloc(sizeof(ListNode));
	list->first->value = (void *)5;
	mu_assert(List_first(list) == (void *)5, "List_first of 5 did not return 5");
	
	return NULL;
}

char *test_list_last()
{
	List *list = List_create();

	mu_assert(List_last(NULL) == NULL, "List_last of NULL did not return NULL");

	list->last = NULL;
	mu_assert(List_last(list) == NULL, "List_last of NULL did not return NULL");
	
	list->last = malloc(sizeof(ListNode));
	list->last->value = (void *)5;
	mu_assert(List_last(list) == (void *)5, "List_last of 5 did not return 5");
	
	return NULL;
}

char *test_list_push()
{
    void *firstElement = (void *)5;
    void *secondElement = (void *)6;
    void *thirdElement = (void *)7;

    List *list = List_create();
    
    List_push(NULL, NULL);
    mu_assert(list->first == NULL, "List_push of null did not return null");

    List_push(list, NULL);
    mu_assert(list->first == NULL, "List_push of null did not return null");
    
    List_push(list, firstElement);
    
    mu_assert(list->count == 1, "Count not incremented upon push");
    
    mu_assert(list->last == list->first, 
            "list_push 1 did not modify last element");
    mu_assert(list->first->value == firstElement, 
            "list_push 1 did not modify first element");
    mu_assert(list->last->value == firstElement, 
            "list_push 1 did not modify last element");

    List_push(list, secondElement);

    mu_assert(list->first->value == firstElement, 
            "list_push 2 modified first element");
    mu_assert(list->last->value == secondElement, 
            "list_push 2 did not modify second element");
    mu_assert(list->last->prev == list->first, 
            "list_push 2 did not modify second element's prev node");
    mu_assert(list->first->next == list->last, 
            "list_push 2 did not modify first element's next node");
    
    List_push(list, thirdElement);
    
	mu_assert(list->first->value == firstElement, 
            "list_push 3 modified first element");
    mu_assert(list->last->value == thirdElement, 
            "list_push 3 did not modify third element");
    mu_assert(list->first->next->value == secondElement, 
            "list_push 3 modified first element's next node");
    mu_assert(list->first->next->next == list->last, 
            "list_push 3 modified first element's next's next node");
			
    mu_assert(list->last->value == thirdElement, 
            "list_push 3 did not modify last element's value");
    mu_assert(list->last->prev->value == secondElement, 
            "list_push 3 did not modify last element's prev value");
    mu_assert(list->last->prev->next == list->last, 
            "list_push 3 did not modify last element's prev node's next value");
    mu_assert(list->last->prev->prev == list->first, 
            "list_push 3 did not modify last element's prev node's prev value");
			
    return NULL;
}

char *test_list_pop()
{
    void *data;
    void *firstElement = (void *)5;
    void *secondElement = (void *)6;
    void *thirdElement = (void *)7;
	
    List *list = List_create();

    data = List_pop(NULL);
    mu_assert(data == NULL, "List_pop of NULL did not return NULL");

	data = List_pop(list);
	mu_assert(data == NULL, "List_pop of NULL did not return NULL");
	
	List_push(list, firstElement);
	data = List_pop(list);
	
	mu_assert(data == firstElement, "List_pop of one element did not return element");
	mu_assert(list->first == NULL, "List_pop of one element did not set first to null");
	mu_assert(list->last == NULL, "List_pop of one element did not set last to null");
	mu_assert(list->count == 0, "List_pop of one element did not modify count");
	
	List_push(list, firstElement);
	List_push(list, secondElement);
	data = List_pop(list);
	
	mu_assert(data == secondElement, "List_pop of two elements did not return second element");
	mu_assert(list->first != NULL, "List_pop of two elements did not delete first node");
	mu_assert(list->last == list->first, "List_pop of two elements did not make last element first");
	mu_assert(list->first->next == NULL, "List_pop of two elements did not make first element's next node null");
	mu_assert(list->last->next == NULL, "List_pop of two elements did not make last element's next node null");
	mu_assert(list->count == 1, "List_pop of two elements did not return correct count")
	
	List_push(list, secondElement);
	List_push(list, thirdElement);
	data = List_pop(list);
	
	mu_assert(data == thirdElement, "List_pop of three elements did not return third element");
	mu_assert(list->last->value == secondElement, "List_pop of three elements did not modify last element");
	mu_assert(list->last->next == NULL, "List_pop of three elements did not modify last element's next node");
	mu_assert(list->first->next == list->last, "List_pop of three elements - first's next does not point to last");
	mu_assert(list->last->prev == list->first, "List_pop of three elements did not modify last element's prev node");
	mu_assert(list->count == 2, "List_pop of three elements did not return correct count");
	
	return NULL;
}

char *test_list_unshift()
{
	void *firstElement = (void *)5;
    void *secondElement = (void *)6;
    void *thirdElement = (void *)7;
	
    List *list = List_create();
	
    List_unshift(NULL, NULL);
    mu_assert(list->first == NULL, "List_unshift of null did not return null");

    List_unshift(list, NULL);
    mu_assert(list->first == NULL, "List_unshift of null did not return null");
	
    List_unshift(list, firstElement);
	mu_assert(list->first != NULL, "List_unshift with no elements did not change first node");
	mu_assert(list->first->value == firstElement, "List_unshift with no elements did not add element");
	mu_assert(list->last != NULL, "List_unshift with no elements did not change last node");
	mu_assert(list->last->value == firstElement, "List_unshift with no elements did not add element");
	mu_assert(list->count == 1, "List_unshift with no elements did not change count");
	
	List_unshift(list, secondElement);
	mu_assert(list->first->value == secondElement, "List_unshift with one element did not prepend value");
	mu_assert(list->last->value == firstElement, "List_unshift with one element modified last value");
	mu_assert(list->first->next == list->last, "List_unshift with one element did not change first node's next node");
	mu_assert(list->first->prev == NULL, "List_unshift with one element changed first node's prev node");
	mu_assert(list->last->prev == list->first, "List_unshift with one element did not change last node's prev node");
	mu_assert(list->last->next == NULL, "List_unshift with one element changed last node's next node");
	mu_assert(list->count == 2, "List_unshift with one elements did not change count");
	
	List_unshift(list, thirdElement);
	mu_assert(list->first->value == thirdElement, "List_unshift with two elements did not prepend value");
	mu_assert(list->first->next->value == secondElement, "List_unshift with two elements did not change first node's next node");
	mu_assert(list->first->next->prev == list->first, "List_unshift with two elements did not change second element's prev node");
	mu_assert(list->first->next->next == list->last, "List_unshift with two elements changed second element's next node");
	
	mu_assert(list->last->value == firstElement, "List_unshift with two elements changed last node");
	mu_assert(list->last->prev->value == secondElement, "List_unshift with two elements changed last node's prev node");
	mu_assert(list->last->prev->next == list->last, "List_unshift with two elements changed last node's prev's next node");
	mu_assert(list->last->prev->prev == list->first, "List_unshift with two elements changed last node's prev's prev node");
	
	return NULL;
}

char *test_list_shift()
{
    List *list = List_create();
    void *data;
    void *firstElement = (void *)5;
    void *secondElement = (void *)6;
	
    data = List_shift(NULL);
    mu_assert(data == NULL, "List_shift of null did not return null");
    
    data = List_shift(list);
    mu_assert(data == NULL, "List_shift of empty list did not return null");
    
    list = List_create();
    List_push(list, firstElement);
    data = List_shift(list);
    mu_assert(data == firstElement, "List_shift of one element did not return first element");
    mu_assert(list->first == NULL, "List_shift of one element did not make first element NULL");
    mu_assert(list->last == NULL, "List_shift of one element did not make last element NULL");
    mu_assert(list->count == 0, "List_shift of one element did not change count");

    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    data = List_shift(list);
    mu_assert(data == firstElement, "List_shift of two elements did not return first element");
    mu_assert(list->first == list->last, "List_shift of two elements did not make first element last");
    mu_assert(list->first->value == secondElement, "List_shift of two elements "
            "modified first element's value");
    mu_assert(list->count == 1, "List_shift of two elements did not change count");

    return NULL;
}

char *test_list_remove()
{
    List *list = List_create();
    void *data;
    void *firstElement = (void *)5;
    void *secondElement = (void *)6;
    void *thirdElement = (void *)7;

    data = List_remove(NULL, NULL);
    mu_assert(data == NULL, "List did not return null when passed null");
    
    data = List_remove(list, NULL);
    mu_assert(data == NULL, "List did not return null when passed null");
	
    list = List_create();
    List_push(list, firstElement);
    data = List_remove(list, list->first);
    
    mu_assert(data == firstElement, "List_remove with one element did not return first element");
    mu_assert(list->count == 0, "List did not decrement count when element was removed");
    mu_assert(list->first == NULL, "List_remove with one element did not remove first node");
    mu_assert(list->last == NULL, "List_remove with one element did not remove last node");
    
    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    data = List_remove(list, list->first);
    
    mu_assert(list->first != NULL, "List_remove(first) with two elements returns null");
    mu_assert(data == firstElement, "List_remove(first) with two elements did not return correct value");
    mu_assert(list->first->prev == NULL, "List_remove(first) with two elements did not delete prev node");
    mu_assert(list->first->next == NULL, "List_remove(first) with two elements did not delete next node");
    mu_assert(list->first == list->last, "List_remove(first) with two elements "
            "did not make first and last node equal");
   
    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    data = List_remove(list, list->last);

    mu_assert(data == secondElement, "List_remove(last) with two elements "
            "did not return correct element");
    mu_assert(list->first == list->last, "List_remove(last) with two elements "
            "did not make first and last equal");
    mu_assert(list->last->value == firstElement, "List_remove(last) with two elements "
            "did not keep correct element");
    mu_assert(list->last->prev == NULL, "List_remove(last) with two element "
            "did not remove prev node");
    mu_assert(list->last->next == NULL, "List_remove(last) with two element "
            "did not remove next node");

    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    List_push(list, thirdElement);
    data = List_remove(list, list->first->next);
   
    mu_assert(data == secondElement, "List_remove(middle) with three elements "
            "did not return corrent element");
    mu_assert(list->first->value == firstElement, "List_remove(middle) with three elements "
            "modified first element");
    mu_assert(list->last->value == thirdElement, "List_remove(middle) with three elements "
            "modified last element");
    mu_assert(list->first->next == list->last, "List_remove(middle) with three elements "
            "did not change first node's next node");
    mu_assert(list->last->prev == list->first, "List_remove(middle) with three elements "
            "did not change last node's prev node");

    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    List_push(list, thirdElement);
    data = List_remove(list, list->first);

    mu_assert(list->first->value == secondElement, "List_remove(first) with three elements "
            "did not change first node's value");
    mu_assert(list->last->value == thirdElement, "List_remove(first) with three elements "
            "modified last node's value");
    mu_assert(list->first->prev == NULL, "List_remove(first) with three elements "
            "did not change first node's prev node");
    mu_assert(list->first->next == list->last, "List_remove(first) with three elements "
            "did not change first node's next node");
    mu_assert(list->last->prev == list->first, "List_remove(first) with three elements "
            "modified last node's prev node");
    mu_assert(list->last->next == NULL, "List_remove(first) with three elements "
            "modified last node's next node");
    
    list = List_create();
    List_push(list, firstElement);
    List_push(list, secondElement);
    List_push(list, thirdElement);
    data = List_remove(list, list->last);

    mu_assert(list->first->value == firstElement, "List_remove(last) with three elements "
            "did not change first node's value");
    mu_assert(list->last->value == secondElement, "List_remove(last) with three elements "
            "modified last node's value");
    mu_assert(list->first->prev == NULL, "List_remove(first) with three elements "
            "changed first node's prev node");
    mu_assert(list->first->next == list->last, "List_remove(first) with three elements "
            "did not change first node's next node");
    mu_assert(list->last->prev == list->first, "List_remove(first) with three elements "
            "did not change last node's prev node");
    mu_assert(list->last->next == NULL, "List_remove(first) with three elements "
            "modified last node's next node");
    
    return NULL;
}

char *test_list_destroy()
{
	List *list = List_create();
	List_push(list, (void *)5);
	List_push(list, (void *)6);
	List_push(list, (void *)7);
	
	List_destroy(list);

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
    mu_run_test(test_list_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
