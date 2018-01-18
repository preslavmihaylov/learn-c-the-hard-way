#ifndef LCTHW_STACK
#define LCTHW_STACK

#include <lcthw/list.h>

typedef List Stack;

#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_clear List_clear
#define Stack_clear_destroy List_clear_destroy

#define Stack_push List_push
#define Stack_pop List_pop
#define Stack_peek List_last

#define Stack_count List_count

#define STACK_FOREACH(curr, stack) LIST_FOREACH(curr, stack)

#endif // LCTHW_STACK
