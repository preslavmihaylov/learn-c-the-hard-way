#include <stdlib.h>
#include <lcthw/ringbuffer.h>
#include <lcthw/dbg.h>

RingBuffer *RingBuffer_create(uint32_t length)
{
    RingBuffer *buffer = NULL;
    check(length > 0, "Length must be positive");

    buffer = calloc(1, sizeof(RingBuffer));
    check_mem(buffer);

    buffer->buffer = calloc(length, sizeof(char*));
    check_mem(buffer->buffer);

    buffer->capacity = length;
    buffer->count = 0;
    buffer->start = 0;
    buffer->end = 0;

    return buffer;

error:
    if (buffer) RingBuffer_destroy(buffer);

    return NULL;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
    if (buffer)
    {
        if (buffer->buffer) free(buffer->buffer);
        free(buffer);
    }
}

int RingBuffer_read(RingBuffer *buffer, char *target, uint32_t amount)
{
    check(buffer != NULL, "RingBuffer cannot be NULL");
    check(target != NULL, "Target cannot be NULL");
    check(amount > 0, "Amount must be greater than 0");
    check(amount <= RingBuffer_available_data(buffer), "Cannot read more than available data");

    for (uint32_t index = 0; index < amount; index++)
    {
        target[index] = buffer->buffer[buffer->start];
        buffer->start = (buffer->start + 1) % buffer->capacity;
    }

    buffer->count -= amount;
    target[amount] = 0;

    return 0;

error:
    return -1;
}

int RingBuffer_peek(RingBuffer *buffer, char *target, uint32_t amount)
{
    check(buffer != NULL, "RingBuffer cannot be NULL");
    check(target != NULL, "Target cannot be NULL");
    check(amount > 0, "Amount must be greater than 0");
    check(amount <= RingBuffer_available_data(buffer), "Cannot peek more than available data");

    for (uint32_t index = 0; index < amount; index++)
    {
        uint32_t bufferIndex = (buffer->start + index) % buffer->capacity;
        target[index] = buffer->buffer[bufferIndex];
    }

    target[amount] = 0;

    return 0;

error:
    return -1;
}

int RingBuffer_write(RingBuffer *buffer, char *data, uint32_t length)
{
    check(buffer != NULL, "RingBuffer cannot be NULL");
    check(data != NULL, "Data cannot be NULL");
    check(length > 0, "Length must be greater than 0");

    for (uint32_t index = 0; index < length; index++)
    {
        if (RingBuffer_full(buffer))
        {
            buffer->start = (buffer->start + 1) % buffer->capacity;
        }

        buffer->buffer[buffer->end] = data[index];
        buffer->end = (buffer->end + 1) % buffer->capacity;
        buffer->count = (buffer->count < buffer->capacity) ? buffer->count + 1 : buffer->count;
    }

    return 0;

error:
    return -1;
}

bool RingBuffer_empty(RingBuffer *buffer)
{
    check(buffer != NULL, "Buffer cannot be NULL");

    return buffer->count == 0;

error:
    return false;
}

bool RingBuffer_full(RingBuffer *buffer)
{
    check(buffer != NULL, "Buffer cannot be NULL");

    return buffer->count == buffer->capacity;

error:
    return false;
}

uint32_t RingBuffer_available_data(RingBuffer *buffer)
{
    check(buffer != NULL, "Buffer cannot be NULL");

    return buffer->count;

error:
    return 0;
}

uint32_t RingBuffer_available_space(RingBuffer *buffer)
{
    check(buffer != NULL, "Buffer cannot be NULL");

    return buffer->capacity - buffer->count;

error:
    return 0;
}

