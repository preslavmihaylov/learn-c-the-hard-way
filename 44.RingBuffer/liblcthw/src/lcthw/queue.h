#ifndef LCTHW_QUEUE
#define LCTHW_QUEUE

#include <lcthw/list.h>

typedef List Queue;

#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_clear List_clear
#define Queue_clear_destroy List_clear_destroy

#define Queue_enqueue List_unshift
#define Queue_dequeue List_pop

#define Queue_peek List_last
#define Queue_count List_count

#define QUEUE_FOREACH(curr, queue) LIST_FOREACH(curr, queue)

#endif // LCTHW_QUEUE
