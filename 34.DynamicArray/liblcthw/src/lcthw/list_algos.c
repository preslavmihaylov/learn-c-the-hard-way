#include <lcthw/list_algos.h>
#include <stdbool.h>
#include <stdio.h>
#include <lcthw/dbg.h>

void printList(char *msg, List *list)
{
	printf("%s", msg);
	LIST_FOREACH(curr, list)
	{
		printf("%s ", (char *)curr->value);
	}
	
	printf("\n");
}

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
            List_push(first, node->value);
        }
        else
        {
            List_push(second, node->value);
        }

        i++;
    }

    first = List_merge_sort(first, cmp);
    second = List_merge_sort(second, cmp);
	
    ListNode *firstNode = first->first;
    ListNode *secondNode = second->first;
    while (firstNode != NULL && secondNode != NULL)
    {
        if (cmp(firstNode->value, secondNode->value) <= 0) 
        {
            List_push(result, firstNode->value);
            firstNode = firstNode->next;
        }
        else
        {
            List_push(result, secondNode->value);
            secondNode = secondNode->next;
        }
    }

    while (firstNode != NULL)
    {
        List_push(result, firstNode->value);
        firstNode = firstNode->next;
    }
    
    while (secondNode != NULL)
    {
        List_push(result, secondNode->value);
        secondNode = secondNode->next;
    }
	
	//printList("RESULT ARRAY: ", result);
    
    List_destroy(first);
    List_destroy(second);

	return result;
}
