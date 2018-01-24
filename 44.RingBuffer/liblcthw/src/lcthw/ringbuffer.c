#include <stdlib.h>
#include <lcthw/ringbuffer.h>
#include <lcthw/dbg.h>

RingBuffer *RingBuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
    check_mem(buffer);

    check(length > 0, "Length must be positive");

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

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
    memcpy(target, buffer->buffer, amount);
    target[amount] = 0;

    return 0;
}

int RingBuffer_peek(RingBuffer *buffer, char *target, int amount)
{
    for (int index = 0; index < amount; index++)
    {
        int bufferIndex = (buffer->start + index) % buffer->capacity;
        target[index] = buffer->buffer[bufferIndex];
    }

    target[amount] = 0;

    return 0;
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    for (int index = 0; index < length; index++)
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
}

bool RingBuffer_empty(RingBuffer *buffer)
{
    return buffer->count == 0;
}

bool RingBuffer_full(RingBuffer *buffer)
{
    return buffer->count == buffer->capacity;
}

int RingBuffer_available_data(RingBuffer *buffer)
{
    return buffer->count;
}

int RingBuffer_available_space(RingBuffer *buffer)
{
    return buffer->capacity - buffer->count;
}

