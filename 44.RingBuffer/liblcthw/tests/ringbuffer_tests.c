#include "minunit.h"
#include <lcthw/ringbuffer.h>

#define BUFFER_SIZE 5

RingBuffer *buffer = NULL;

char *test_create()
{
    buffer = RingBuffer_create(BUFFER_SIZE);
    mu_assert(buffer != NULL, "Failed to create Ring buffer");

    return NULL;
}

char *test_read_write()
{
    int rc = 0;
    char target[50];
    for (int i = 0; i < 50; i++)
    {
        target[i] = 1;
    }

    mu_assert(RingBuffer_empty(buffer) == true, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == false, "RingBuffer_full wrong return value");

    rc = RingBuffer_write(buffer, "1234", 4);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 4, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 1, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");

    rc = RingBuffer_read(buffer, target, 4);
    mu_assert(rc == 0, "Ringbuffer_read bad exit status");
    mu_assert(strcmp(target, "1234") == 0, "Bad data after read");

    rc = RingBuffer_write(buffer, "5", 1);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 5, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 0, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == true, "RingBuffer_full wrong return value");

    rc = RingBuffer_read(buffer, target, 5);
    mu_assert(rc == 0, "Ringbuffer_read bad exit status");

    log_info("ASSERT Expected: %s, Actual: %s", "12345", target);
    mu_assert(strcmp(target, "12345") == 0, "Bad data after read 2");

    return NULL;
}

char *test_destroy()
{
    RingBuffer_destroy(buffer);

    return NULL;
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
