#ifndef LCTHW_RINGBUFFER_H
#define LCTHW_RINGBUFFER_H

#include <lcthw/bstrlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    char *buffer;
    uint32_t capacity;
    uint32_t count;
    uint32_t start;
    uint32_t end;
} RingBuffer;

RingBuffer *RingBuffer_create(uint32_t length);
void RingBuffer_destroy(RingBuffer *buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, uint32_t amount);
int RingBuffer_peek(RingBuffer *buffer, char *target, uint32_t amount);
int RingBuffer_write(RingBuffer *buffer, char *data, uint32_t length);

bool RingBuffer_empty(RingBuffer *buffer);
bool RingBuffer_full(RingBuffer *buffer);
uint32_t RingBuffer_available_data(RingBuffer *buffer);
uint32_t RingBuffer_available_space(RingBuffer *buffer);

#endif // LCTHW_RINGBUFFER_H
