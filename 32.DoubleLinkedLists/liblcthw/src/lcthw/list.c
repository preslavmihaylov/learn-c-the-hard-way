#include <list.h>
#include <stdlib.h>
#include <assert.h>
#include <dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
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
        return list->first->value;
    return NULL;
}

void *List_last(List *list)
{
    return NULL;
}

void List_push(List *list, void *value)
{
    ListNode *node = malloc(sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL)
    {
        assert(list->last == NULL);

        list->first = node;
        list->last = node;
    }
    else
    {
        list->last = node;
    }
        
    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    return NULL;
}

void List_unshift(List *list, void *value)
{

}

void *List_shift(List *list)
{
    return NULL;
}

void *List_remove(List *list, ListNode *node)
{
    return NULL;
}
