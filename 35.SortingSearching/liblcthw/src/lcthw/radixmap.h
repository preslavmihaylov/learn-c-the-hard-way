#ifndef RADIXMAP_H
#define RADIXMAP_H

#include <string.h>
#include <stdint.h>

typedef union RMElement
{
	uint64_t raw;
	struct {
		uint32_t key;
		uint32_t value;
	} data;
} RMElement;

typedef struct RadixMap
{
	size_t capacity;
	size_t count;
	uint32_t counter;
	RMElement *contents;
	RMElement *temp;
} RadixMap;

RadixMap *RadixMap_create(size_t capacity);
void RadixMap_destroy(RadixMap *map);
void RadixMap_sort(RadixMap *map);
RMElement *RadixMap_find(RadixMap *map, uint32_t key);
int RadixMap_add(RadixMap *map, uint32_t key, uint32_t value);
int RadixMap_delete(RadixMap *map, RMElement *el);

#endif // RADIXMAP_H
