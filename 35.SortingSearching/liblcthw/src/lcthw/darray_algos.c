#include <lcthw/darray_algos.h>
#include <bsd/stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), array->element_size, cmp);
	return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	return heapsort(array->contents, DArray_count(array), array->element_size, cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	return mergesort(array->contents, DArray_count(array), array->element_size, cmp);
}
