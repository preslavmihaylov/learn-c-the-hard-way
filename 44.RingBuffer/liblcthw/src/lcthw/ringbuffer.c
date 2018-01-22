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

    buffer->length = length;
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

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    memcpy(buffer->buffer + buffer->end, data, length);
    buffer->end += length;

    return 0;
}

bool RingBuffer_empty(RingBuffer *buffer)
{
    return RingBuffer_available_space(buffer) == buffer->length;
}

bool RingBuffer_full(RingBuffer *buffer)
{
    return buffer->end == buffer->length;
}

int RingBuffer_available_data(RingBuffer *buffer)
{
    return buffer->end;
}

int RingBuffer_available_space(RingBuffer *buffer)
{
    return (buffer->length - buffer->end);
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
    return NULL;
}

