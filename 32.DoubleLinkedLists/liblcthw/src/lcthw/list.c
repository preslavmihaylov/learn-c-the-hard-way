#include <list.h>
#include <stdlib.h>
#include <assert.h>
#include <dbg.h>

static ListNode *List_createNode();

List *List_create()
{
	List *list = calloc(1, sizeof(List));
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	
    return list;
}

void List_destroy(List *list)
{
    // TODO:
    /*
    for (ListNode *node = list->first; node != NULL; node = node->next)
        free(node->prev);
    
    if (list->last)
        free(list->last);
    free(list);
    */
}

void List_clear(List *list)
{
    // TODO:
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

int List_count(List *list)
{
    return list->count;
}

void *List_first(List *list)
{
    if (list->first)
	{
		assert(list->first->value != NULL);
        return list->first->value;
	}
	
	return NULL;
}

void *List_last(List *list)
{
	if (list->last)
	{
		assert(list->last->value != NULL);
		return list->last->value;
	}
        
    return NULL;
}

void List_push(List *list, void *value)
{
    ListNode *node = List_createNode();
    check_mem(node);

    node->value = value;

    if (list->count == 0)
    {
        assert(list->last == NULL && list->first == NULL);

        list->first = node;
        list->last = list->first;
    }
    else
    {
		node->prev = list->last;
		list->last->next = node;
		
        list->last = node;
    }
        
    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
	if (list->count == 0)
		return NULL;
	
	ListNode *node = list->last;
	void *data = node->value;
	
	list->last = list->last->prev;
	
	if (list->last)
		list->last->next = NULL;
	else
		list->first = NULL;
	
	list->count--;
	free(node);
	
	return data;
}

void List_unshift(List *list, void *value)
{
	ListNode *node = List_createNode();
	check_mem(node);

	node->value = value;
	
	if (list->count == 0)
	{
		list->last = node;	
	}
	else
	{
		node->next = list->first;
		list->first->prev = node;
	}
	
	list->first = node;
	list->count++;
	
error:
	return;
}

void *List_shift(List *list)
{
    return NULL;
}

void *List_remove(List *list, ListNode *node)
{
    return NULL;
}

static ListNode *List_createNode()
{
	ListNode *node = malloc(sizeof(ListNode));
	node->prev = NULL;
	node->next = NULL;
	node->value = NULL;
	
	return node;
}
