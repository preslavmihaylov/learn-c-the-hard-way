#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;
typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

int List_count(List *list);
void *List_first(List *list);
void *List_last(List *list);

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

#define LIST_FOREACH(curr, list) \
	ListNode *curr = list->first;\
    for (ListNode *_node = list->first; \
         _node != NULL; \
         curr = _node = _node->next)

#endif // lcthw_List_h
