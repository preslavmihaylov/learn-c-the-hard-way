#ifndef LCTHW_RINGBUFFER_H
#define LCTHW_RINGBUFFER_H

#include <lcthw/bstrlib.h>
#include <stdbool.h>

typedef struct
{
    char *buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);
void RingBuffer_destroy(RingBuffer *buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);
int RingBuffer_write(RingBuffer *buffer, char *data, int length);

bool RingBuffer_empty(RingBuffer *buffer);
bool RingBuffer_full(RingBuffer *buffer);
int RingBuffer_available_data(RingBuffer *buffer);
int RingBuffer_available_space(RingBuffer *buffer);

bstring RingBuffer_gets(RingBuffer *buffer, int amount);

#endif // LCTHW_RINGBUFFER_H
