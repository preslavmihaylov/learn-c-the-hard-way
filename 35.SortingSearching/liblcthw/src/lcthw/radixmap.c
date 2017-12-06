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
	// TODO:
	return -1;
}

int RadixMap_delete(RadixMap *map, RMElement *el)
{
	// TODO:
	return -1;
}

