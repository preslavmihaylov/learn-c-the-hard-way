#ifndef LCTHW_DARRAY_H
#define LCTHW_DARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

#define DEFAULT_EXPAND_RATE 300

typedef struct DArray {
    int count;
    int max;
    size_t element_size;
    size_t expand_rate;
    void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
int DArray_expand(DArray *array);
int DArray_contract(DArray *array);
int DArray_push(DArray *array, void *el);
void *DArray_pop(DArray *array);
void DArray_clear_destroy(DArray *array);

void *DArray_last(DArray *array);
void *DArray_first(DArray *array);
size_t DArray_count(DArray *array);
size_t DArray_max(DArray *array);

void DArray_set(DArray *array, int i, void *el);
void *DArray_get(DArray *array, int i);
void *DArray_remove(DArray *array, int i);
void *DArray_new(DArray *array);
void DArray_free(void *element);

#endif // LCTHW_DARRAY_H
