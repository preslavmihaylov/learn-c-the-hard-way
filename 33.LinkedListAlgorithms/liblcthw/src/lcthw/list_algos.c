#include <lcthw/list_algos.h>
#include <stdbool.h>
#include <stdio.h>

void List_swap_nodes(ListNode *first, ListNode *second)
{
    void *tmp = first->value;
    first->value = second->value;
    second->value = tmp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    bool sorted = false;
	while (!sorted)
	{
        sorted = true;
        LIST_FOREACH(node, list) 
        {
            if (!node->next) continue;

            if (cmp(node->value, node->next->value) > 0) 
            {
                List_swap_nodes(node, node->next);
                
                sorted = false;
            }
        }
	}

	return 0;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if (List_count(list) <= 1) return list;

    List *first = List_create();
    List *second = List_create();
    List *result = List_create();

    int i = 0;
    LIST_FOREACH(node, list)
    {
        if (i < List_count(list) / 2)
        {
            List_unshift(first, node->value);
        }
        else
        {
            List_unshift(second, node->value);
        }

        i++;
    }

    printf("FIRST: ");
    LIST_FOREACH(firstI, first)
    {
        printf("%s ", (char *)firstI->value);
    }
    printf("\n");

    printf("SECOND: ");
    LIST_FOREACH(secondI, second)
    {
        printf("%s ", (char *)secondI->value);
    }
    printf("\n");
    
    // TODO: recursive call
    first = List_merge_sort(first, cmp);
    second = List_merge_sort(second, cmp);
    
    // TODO: This is failing
    ListNode *firstNode = first->first;
    ListNode *secondNode = second->first;
    while (firstNode != NULL && secondNode != NULL)
    {
        if (cmp(firstNode->value, secondNode->value) <= 0) 
        {
            List_unshift(result, firstNode->value);
            firstNode = firstNode->next;
        }
        else
        {
            List_unshift(result, secondNode->value);
            secondNode = secondNode->next;
        }
    }

    while (firstNode != NULL)
    {
        List_unshift(result, firstNode->value);
        firstNode = firstNode->next;
    }
    
    while (secondNode != NULL)
    {
        List_unshift(result, secondNode->value);
        secondNode = secondNode->next;
    }
    
    List_destroy(first);
    List_destroy(second);

	return result;
}
