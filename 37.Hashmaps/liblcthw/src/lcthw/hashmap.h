#ifndef LCTHW_HASHMAP_H
#define LCTHW_HASHMAP_H

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUM_BUCKETS 100

typedef int (*Hashmap_compare) (void *a, void *b);
typedef uint32_t (*Hashmap_hash) (void *key);

typedef struct Hashmap
{
	DArray *buckets;
	Hashmap_compare compare;
	Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode
{
	void *key;
	void *data;
	uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb) (HashmapNode *node);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap *map, void *key, void *data);
void *Hashmap_get(Hashmap *map, void *key);

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

void *Hashmap_delete(Hashmap *map, void *key);

#endif // LCTHW_HASHMAP_H
