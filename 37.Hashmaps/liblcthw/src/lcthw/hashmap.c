#include <lcthw/hashmap.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b)
{
	return bstrcmp((bstring)a, (bstring)b);
}

/**
 * Simple Bob Jenkins's hash algorithm taken from wikipedia
 */
static uint32_t default_hash(void* key) {
	uint32_t length = blength((bstring)key);
	bstring str = (bstring)key;

	uint32_t i = 0;
	uint32_t hash = 0;
	
	while (i != length) {
		hash += bchar(str, i);
		i++;
		
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	
	return hash;
}

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash)
{
	Hashmap *map = malloc(sizeof(Hashmap));
	check_mem(map);

	map->buckets = DArray_create(sizeof(DArray *), DEFAULT_NUM_BUCKETS);
	check_mem(map->buckets);

	// initialize darray with 100 empty elements
	map->buckets->count = map->buckets->capacity;

	map->compare = compare != NULL ? compare : default_compare;
	map->hash = hash != NULL ? hash : default_hash;

	return map;

error:
	Hashmap_destroy(map);
	return NULL;
}

void Hashmap_destroy(Hashmap *map)
{
	if (!map) return;

	if (map->buckets)
	{
		for (uint32_t i = 0; i < DArray_count(map->buckets); ++i)
		{
			DArray *bucket = DArray_get(map->buckets, i);
			if (!bucket) continue;

			for (uint32_t j = 0; j < DArray_count(bucket); ++i)
			{
				DArray_destroy(DArray_get(bucket, j));
			}

			DArray_destroy(bucket);
		}

		DArray_destroy(map->buckets);
	}

	free(map);
}

int Hashmap_set(Hashmap *map, void *key, void *data)
{
	// TODO:
	return 0;
}

void *Hashmap_get(Hashmap *map, void *key)
{
	// TODO:
	return NULL;
}

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb)
{
	// TODO:
	return 0;
}

void *Hashmap_delete(Hashmap *map, void *key)
{
	// TODO:
	return NULL;
}
