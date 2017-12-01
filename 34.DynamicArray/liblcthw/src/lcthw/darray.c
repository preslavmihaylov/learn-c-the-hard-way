#include <lcthw/darray.h>

DArray *DArray_create(size_t element_size, size_t initial_capacity)
{
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    
    check(element_size != 0, "element size cannot be 0");
    check(initial_capacity > 0, 
		"Initial capacity should be greater than 0");

    array->contents = calloc(array->capacity, sizeof(void *));
    check_mem(array->contents);

    array->count = 0;
    array->capacity = initial_capacity;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

error:
    DArray_destroy(array);
    return NULL;

}

void DArray_destroy(DArray *array)
{
    if (array)
    {
        if (array->contents) free(array->contents);
        free(array);
    }
}

void DArray_clear(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
    check(array->contents != NULL, "Array contents cannot be NULL");

    for (size_t i = 0; i < array->count; ++i)
    {
        DArray_free(array->contents[i]);
    }

error: // fallthrough
    return;
}

void DArray_clear_destroy(DArray *array)
{
    DArray_clear(array);
    DArray_destroy(array);
}

void *DArray_new(DArray *array)
{
    check(array != NULL, "Passed null array");
    check(array->element_size != 0, "element size cannot be 0");

    void *element = malloc(sizeof(array->element_size));
    
    return element;

error:
    return NULL;
}

void DArray_free(void *element)
{
    free(element);
}

size_t DArray_expand(DArray *array)
{
    // TODO
    return 0;
}

size_t DArray_contract(DArray *array)
{
    // TODO
    return 0;
}

int DArray_push(DArray *array, void *el)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	
	if (array->count >= array->capacity)
	{
		// TODO: Expand
	}

    array->contents[array->count++] = el;

    return 0;

error:
	return -1;
}

void *DArray_pop(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	
	void *el = array->contents[--array->count];
	if (array->count > array->expand_rate &&
		array->count % array->expand_rate == 0)
	{
		// TODO: contract
	}

    return  el;

error:
	return NULL;
}

void *DArray_remove(DArray *array, size_t i)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	check(i < array->count, "index out of range");

	void *el = array->contents[i];
	array->contents[i] = NULL;

	return el;

error:
    return NULL;
}

void DArray_set(DArray *array, size_t i, void *el)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	check(i < array->count, "index out of range");

	array->contents[i] = el;

error: // fallthrough
	return;
}

void *DArray_get(DArray *array, size_t i)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	check(i < array->count, "index out of range");

	return array->contents[i];

error:
	return NULL;
}

void *DArray_last(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	check(array->count > 0, "Array count is 0");

	return array->contents[array->count - 1];

error:
	return NULL;
}

void *DArray_first(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
	check(array->contents != NULL, "Array contents cannot be NULL");
	check(array->count > 0, "Array count is 0");

	return array->contents[0];

error:
	return NULL;
}

size_t DArray_count(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
    return array->count;

error:
    return 0;
}

size_t DArray_capacity(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
    return array->capacity;

error:
    return 0;
}
