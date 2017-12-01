#include <lcthw/darray.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    
    check(element_size != 0, "element size cannot be 0");
    check(initial_max > 0, "Initial max should be greater than 0");

    array->contents = calloc(array->max, sizeof(void *));
    check_mem(array->contents);

    array->count = 0;
    array->max = initial_max;
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

    for (int i = 0; i < array->count; ++i)
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

int DArray_expand(DArray *array)
{
    // TODO
    return 0;
}

int DArray_contract(DArray *array)
{
    // TODO
    return 0;
}

int DArray_push(DArray *array, void *el)
{
    // TODO
    return 0;
}

void *DArray_pop(DArray *array)
{
    // TODO
    return NULL;
}

void *DArray_last(DArray *array)
{
    // TODO
    return NULL;
}

void *DArray_first(DArray *array)
{
    // TODO
    return NULL;
}

size_t DArray_count(DArray *array)
{
    check(array != NULL, "Array cannot be NULL");
    return array->count;

error:
    return 0;
}

size_t DArray_max(DArray *array)
{
    // TODO
    return 0;
}

void DArray_set(DArray *array, int i, void *el)
{
    // TODO
}

void *DArray_get(DArray *array, int i)
{
    // TODO
    return NULL;
}

void *DArray_remove(DArray *array, int i)
{
    // TODO
    return NULL;
}

