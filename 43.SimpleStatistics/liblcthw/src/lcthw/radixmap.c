#include <lcthw/radixmap.h>
#include <lcthw/dbg.h>
#include <stdlib.h>
#include <darray.h>
#include <assert.h>

#define SIZEOF_BYTE 256
#define ByteOf(num, byteIndex) (((num) >> ((byteIndex) * 8)) & 0xFF)

static RMElement * RadixMap_binarySearch(RMElement *contents, uint32_t min, uint32_t max, uint32_t key);
static void RadixMap_radixSort(RMElement *contents, uint32_t count, int byte);
static void RadixMap_sortByByte(RMElement *contents, 
								uint32_t count, 
								int byte);

RadixMap *RadixMap_create(uint32_t capacity)
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
	RadixMap_radixSort(map->contents, map->count, 3);
}

RMElement *RadixMap_find(RadixMap *map, uint32_t key)
{
	return RadixMap_binarySearch(map->contents, 0, map->count, key);
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

static RMElement * RadixMap_binarySearch(RMElement *contents, uint32_t min, uint32_t max, uint32_t key)
{
	if (min >= max) return NULL;

	uint32_t mid = (min + max) / 2;
	if (contents[mid].data.key < key)
	{
		return RadixMap_binarySearch(contents, mid + 1, max, key);
	}
	else if (contents[mid].data.key > key)
	{
		return RadixMap_binarySearch(contents, min, mid, key);
	}
	else
	{
		return &contents[mid];
	}
}

static void RadixMap_radixSort(RMElement *contents, uint32_t count, int byte)
{
	if (byte < 0) return;
	
	RadixMap_radixSort(contents, count, byte - 1);
	RadixMap_sortByByte(contents, count, byte);
}

static void RadixMap_sortByByte(RMElement *contents, 
								uint32_t count, 
								int byte)
{
	DArray *buckets[SIZEOF_BYTE] = { NULL };
	uint32_t i;

	for (i = 0; i < count; ++i)
	{
		int currentByte = ByteOf(contents[i].raw, byte);
		if (buckets[currentByte] == NULL)
		{
			buckets[currentByte] = DArray_create(sizeof(uint64_t), 2); 
		}

		DArray_push(buckets[currentByte], (void*)contents[i].raw);
	}

	uint32_t contentsIndex = 0;
	for (i = 0; i < SIZEOF_BYTE; ++i)
	{
		if (buckets[i] == NULL) continue;

		for (uint32_t j = 0; j < DArray_count(buckets[i]); ++j)
		{
			contents[contentsIndex++].raw = (uint64_t)DArray_get(buckets[i], j);
		}

		DArray_destroy(buckets[i]);
	}

	// sorted as much elements as in the beginning
	assert(contentsIndex == count);
}
