#ifndef LCTHW_LIST_ALGOS_H
#define LCTHW_LIST_ALGOS_H

#include <lcthw/list.h>

typedef int (*List_compare) (const void *, const void *);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif // LCTHW_LIST_ALGOS_H
