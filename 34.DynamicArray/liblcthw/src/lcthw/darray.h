#ifndef LCTHW_DARRAY_H
#define LCTHW_DARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

#define DEFAULT_EXPAND_RATE 300

typedef struct DArray {
    size_t count;
    size_t capacity;
    size_t element_size;
    size_t expand_rate;
    void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_capacity);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
void DArray_clear_destroy(DArray *array);
void *DArray_new(DArray *array);
void DArray_free(void *element);
int DArray_expand(DArray *array);
size_t DArray_contract(DArray *array);
int DArray_push(DArray *array, void *el);
void *DArray_pop(DArray *array);
void *DArray_remove(DArray *array, size_t i);
void DArray_set(DArray *array, size_t i, void *el);
void *DArray_get(DArray *array, size_t i);
void *DArray_last(DArray *array);
void *DArray_first(DArray *array);
size_t DArray_count(DArray *array);
size_t DArray_capacity(DArray *array);

#endif // LCTHW_DARRAY_H
