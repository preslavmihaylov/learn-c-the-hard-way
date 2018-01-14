#ifndef DARRAY_ALGOS_H
#define DARRAY_ALGOS_H

#include <lcthw/darray.h>

typedef int (*DArray_compare)(const void *first, const void *second);

int DArray_qsort(DArray *array, DArray_compare cmp);
int DArray_heapsort(DArray *array, DArray_compare cmp);
int DArray_mergesort(DArray *array, DArray_compare cmp);

#endif // DARRAY_ALGOS_H
