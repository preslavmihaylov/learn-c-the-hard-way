#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>
#include <stdlib.h>

RadixMap *RadixMap_create(size_t capacity)
{
	check(capacity > 0, "capacity has to be greater than 0");
	
	RadixMap *map = malloc(sizeof(RadixMap));
	check_mem(map);

	map->contents = calloc(capacity, sizeof(RMElement));
	map->capacity = capacity;
	map->count = 0;	

	return map;
error:
	RadixMap_destroy(map);
	return NULL;
}

void RadixMap_destroy(RadixMap *map)
{
	if (map)
	{
		if (map->contents) free(map->contents);
		free(map);
	}
}

void RadixMap_sort(RadixMap *map)
{
	// TODO:
}

RMElement *RadixMap_find(RadixMap *map, uint32_t key)
{
	// TODO:
	return NULL;
}

int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value)
{
	check(key != UINT32_MAX, "Key cannot be equal to UINT32_MAX");
	check(map->count < map->capacity, "Radix map is full");

	RMElement el = { .data = { .key = key, .value = value } };
	map->contents[map->count++] = el;

	RadixMap_sort(map);
	return 0;

error:
	return -1;
}

int RadixMap_delete(RadixMap *map, RMElement *el)
{
	check(map->count > 0, "RadixMap is empty when attempting to delete");
	check(el != NULL, "element to delete is NULL");

	el->data.key = UINT32_MAX;
	--map->count;
	
	RadixMap_sort(map);
	return 0;

error:
	return -1;
}

static void RadixMap_radixSort(RMElement *contents, size_t count, int byte)
{
	if (byte < 0) return;

	RadixMap_radixSort(contents, count, byte - 1);
	RadixMap_sortByByte(contents, count, byte);
}

static void RadixMap_sortByByte(RMElement *contents, 
								size_t count, 
								int byte)
{
	// TODO:
}
