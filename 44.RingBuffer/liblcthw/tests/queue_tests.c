#include "minunit.h"
#include <lcthw/queue.h>
#include <assert.h>

static Queue *queue = NULL;
char *tests[] = { "test1 data", "test2 data", "test3 data" };

#define NUM_TESTS 3

char *test_create()
{
    queue = Queue_create();
    mu_assert(queue != NULL, "Failed to create queue");

    return NULL;
}

char *test_destroy()
{
    mu_assert(queue != NULL, "Failed to make queue #2");
    Queue_destroy(queue);

    return NULL;
}

char *test_enqueue_dequeue()
{
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++)
    {
        Queue_enqueue(queue, tests[i]);
        mu_assert(Queue_peek(queue) == tests[0], "Wrong next value");
    }

    mu_assert(Queue_count(queue) == NUM_TESTS, "Wrong count on enqueue");

    QUEUE_FOREACH(curr, queue)
    {
        debug("VAL: %s", (char *)curr->value);
    }

    for (i = 0; i < NUM_TESTS; i++)
    {
        char *val = Queue_dequeue(queue);
        mu_assert(val == tests[i], "Wrong value on dequeue");
    }

    mu_assert(Queue_count(queue) == 0, "Wrong count after dequeue");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_enqueue_dequeue);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
