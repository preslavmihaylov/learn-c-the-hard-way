#ifndef LCTHW_DARRAY_H
#define LCTHW_DARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <lcthw/dbg.h>

#define DEFAULT_EXPAND_RATE 300

typedef struct DArray {
    uint32_t count;
    uint32_t capacity;
    uint32_t element_size;
    uint32_t expand_rate;
    void **contents;
} DArray;

DArray *DArray_create(uint32_t element_size, uint32_t initial_capacity);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
void DArray_clear_destroy(DArray *array);
void *DArray_new(DArray *array);
void DArray_free(void *element);
int DArray_expand(DArray *array);
int DArray_contract(DArray *array);
int DArray_push(DArray *array, void *el);
void *DArray_pop(DArray *array);
void *DArray_remove(DArray *array, uint32_t i);
void DArray_set(DArray *array, uint32_t i, void *el);
void *DArray_get(DArray *array, uint32_t i);
void *DArray_last(DArray *array);
void *DArray_first(DArray *array);
uint32_t DArray_count(DArray *array);
uint32_t DArray_capacity(DArray *array);

#endif // LCTHW_DARRAY_H
