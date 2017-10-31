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
	ListNode *node;
    for (node = list->first; node != NULL; node = node->next)
        free(node->prev);

    free(node);
    free(list);
}

void List_clear(List *list)
{
    for (ListNode *node = list->first; node != NULL; node = node->next)
        free(node->value);
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

int List_count(List *list)
{
    if (!list) return 0;

    return list->count;
}

void *List_first(List *list)
{
    if (!list || !list->first) return NULL;
    assert(list->first->value != NULL);
    
    return list->first->value;
}

void *List_last(List *list)
{
    if (!list || !list->last) return NULL;
    assert(list->last->value != NULL);
    
    return list->last->value;    
}

void List_push(List *list, void *value)
{
    if (!list || !value) return;

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
	if (!list) return NULL;
	
	return List_remove(list, list->last);	
}

void List_unshift(List *list, void *value)
{
    if (!list || !value) return;

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
    if (!list) return NULL;

    return List_remove(list, list->first);
}

void *List_remove(List *list, ListNode *node)
{
    if (list == NULL || node == NULL || list->count == 0) return NULL;
    
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        assert(node == list->first);
        list->first = node->next;
    }

    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        assert(node == list->last);
        list->last = node->prev;
    }

    list->count--;
    void *data = node->value;
	free(node);    

    return data;
}

static ListNode *List_createNode()
{
	ListNode *node = malloc(sizeof(ListNode));
	node->prev = NULL;
	node->next = NULL;
	node->value = NULL;
	
	return node;
}
