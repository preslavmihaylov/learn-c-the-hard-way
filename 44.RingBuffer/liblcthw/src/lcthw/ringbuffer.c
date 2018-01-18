#include <lcthw/ringbuffer.h>

RingBuffer *RingBuffer_create(int length)
{
    return NULL;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
    return;
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

