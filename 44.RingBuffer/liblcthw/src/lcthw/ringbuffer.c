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
    return 0;
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    return 0;
}


bool RingBuffer_empty(RingBuffer *buffer)
{
    return true;
}

bool RingBuffer_full(RingBuffer *buffer)
{
    return true;
}

int RingBuffer_available_data(RingBuffer *buffer)
{
    return 0;
}

int RingBuffer_available_space(RingBuffer *buffer)
{
    return 0;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
    return NULL;
}

