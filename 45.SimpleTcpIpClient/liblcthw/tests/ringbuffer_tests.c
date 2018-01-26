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

    RingBuffer *invalidBuffer = RingBuffer_create(0);
    mu_assert(invalidBuffer == NULL, "RingBuffer_create created buffer with length 0");

    rc = RingBuffer_read(NULL, target, 5);
    mu_assert(rc != 0, "RingBuffer_read succeeded when ringbuffer is null");

    rc = RingBuffer_write(NULL, "1234", 5);
    mu_assert(rc != 0, "RingBuffer_write succeeded when ringbuffer is null");

    rc = RingBuffer_peek(NULL, target, 5);
    mu_assert(rc != 0, "RingBuffer_peek succeeded when ringbuffer is null");

    mu_assert(RingBuffer_empty(NULL) == false, "RingBuffer_empty returned true with NULL");
    mu_assert(RingBuffer_full(NULL) == false, "RingBuffer_full returned true with NULL");
    mu_assert(
        RingBuffer_available_data(NULL) == 0, "RingBuffer_available_data succeeded when input is NULL");
    mu_assert(
        RingBuffer_available_space(NULL) == 0, "RingBuffer_available_space succeeded when input is NULL");

    mu_assert(RingBuffer_empty(buffer) == true, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == false, "RingBuffer_full wrong return value");

    rc = RingBuffer_peek(buffer, "1", 1);
    mu_assert(rc != 0, "RingBuffer_peek expected to return error code, but was successful");

    rc = RingBuffer_read(buffer, "1", 1);
    mu_assert(rc != 0, "RingBuffer_read expected to return error code, but was successful");

    rc = RingBuffer_write(buffer, "", 0);
    mu_assert(rc != 0, "RingBuffer_write succeeded with length 0");

    rc = RingBuffer_write(buffer, "1234", 4);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 4, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 1, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");

    rc = RingBuffer_peek(buffer, target, 4);
    mu_assert(rc == 0, "Ringbuffer_peek bad exit status");
    mu_assert(strcmp(target, "1234") == 0, "Bad data after peek");

    rc = RingBuffer_peek(buffer, NULL, 4);
    mu_assert(rc != 0, "RingBuffer_peek succeeded when target is null");

    rc = RingBuffer_read(buffer, NULL, 4);
    mu_assert(rc != 0, "RingBuffer_read succeeded when target is null");

    rc = RingBuffer_read(buffer, "", 0);
    mu_assert(rc != 0, "RingBuffer_read succeeded when amount is 0");

    rc = RingBuffer_peek(buffer, "", 0);
    mu_assert(rc != 0, "RingBuffer_peek succeeded when amount is 0");

    rc = RingBuffer_write(buffer, NULL, 4);
    mu_assert(rc != 0, "RingBuffer_write succeeded when data is NULL");

    rc = RingBuffer_write(buffer, "5", 1);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");

    mu_assert(RingBuffer_available_data(buffer) == 5, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 0, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == true, "RingBuffer_full wrong return value");

    rc = RingBuffer_peek(buffer, target, 5);
    mu_assert(rc == 0, "Ringbuffer_peek bad exit status");

    log_info("ASSERT Expected: %s, Actual: %s", "12345", target);
    mu_assert(strcmp(target, "12345") == 0, "Bad data after peek");

    rc = RingBuffer_write(buffer, "6", 1);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 5, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 0, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == true, "RingBuffer_full wrong return value");

    rc = RingBuffer_peek(buffer, target, 5);
    mu_assert(rc == 0, "Ringbuffer_peek bad exit status");

    log_info("ASSERT Expected: %s, Actual: %s", "23456", target);
    mu_assert(strcmp(target, "23456") == 0, "Bad data after peek");

    rc = RingBuffer_write(buffer, "789", 3);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 5, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 0, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == true, "RingBuffer_full wrong return value");

    rc = RingBuffer_peek(buffer, target, 5);
    mu_assert(rc == 0, "Ringbuffer_peek bad exit status");

    log_info("ASSERT Expected: %s, Actual: %s", "56789", target);
    mu_assert(strcmp(target, "56789") == 0, "Bad data after peek");

    RingBuffer_read(buffer, target, 2);
    mu_assert(rc == 0, "RingBuffer_read bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 3, "wrong available data after Ringbuffer_read");
    mu_assert(RingBuffer_available_space(buffer) == 2, "wrong available space after RingBuffer_read");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == false, "RingBuffer_full wrong return value");

    log_info("ASSERT Expected: %s, Actual: %s", "56", target);
    mu_assert(strcmp(target, "56") == 0, "Bad data after read");

    rc = RingBuffer_write(buffer, "1", 1);
    mu_assert(rc == 0, "RingBuffer_write bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 4, "wrong available data after Ringbuffer_write");
    mu_assert(RingBuffer_available_space(buffer) == 1, "wrong available space after RingBuffer_write");
    mu_assert(RingBuffer_empty(buffer) == false, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == false, "RingBuffer_full wrong return value");

    rc = RingBuffer_peek(buffer, target, 4);
    mu_assert(rc == 0, "Ringbuffer_peek bad exit status");

    log_info("ASSERT Expected: %s, Actual: %s", "7891", target);
    mu_assert(strcmp(target, "7891") == 0, "Bad data after peek");

    RingBuffer_read(buffer, target, 4);
    mu_assert(rc == 0, "RingBuffer_read bad exit status");
    mu_assert(RingBuffer_available_data(buffer) == 0, "wrong available data after Ringbuffer_read");
    mu_assert(RingBuffer_available_space(buffer) == 5, "wrong available space after RingBuffer_read");
    mu_assert(RingBuffer_empty(buffer) == true, "RingBuffer_empty wrong return value");
    mu_assert(RingBuffer_full(buffer) == false, "RingBuffer_full wrong return value");

    log_info("ASSERT Expected: %s, Actual: %s", "7891", target);
    mu_assert(strcmp(target, "7891") == 0, "Bad data after read");

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
