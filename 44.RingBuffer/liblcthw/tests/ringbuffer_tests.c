#include "minunit.h"
#include <lcthw/ringbuffer.h>

RingBuffer *buffer = NULL;

char *test_create()
{
    buffer = RingBuffer_create(50);
    mu_assert(buffer != NULL, "Failed to create Ring buffer");

    return NULL;
}

char *test_read_write()
{

}

char *test_destroy()
{
    RingBuffer_destroy(buffer);
}
/*
RingBuffer *RingBuffer_create(int length);
void RingBuffer_destroy(RingBuffer *buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);
int RingBuffer_write(RingBuffer *buffer, char *data, int length);

bool RingBuffer_empty(RingBuffer *buffer);
bool RingBuffer_full(RingBuffer *buffer);
int RingBuffer_available_data(RingBuffer *buffer);
int RingBuffer_available_space(RingBuffer *buffer);

bstring RingBuffer_gets(RingBuffer *buffer, int amount);
*/

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
