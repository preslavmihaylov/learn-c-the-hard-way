#include <lcthw/hashmap.h>
#include <lcthw/bstrlib.h>
#include <assert.h>

static int default_compare(void *a, void *b);
static uint32_t default_hash(void* key);
static inline int Hashmap_findBucketIndex(Hashmap *map, void *key);
static inline HashmapNode *HashmapNode_create(void *key, void *value);


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

            for (uint32_t j = 0; j < DArray_count(bucket); ++j)
            {
                DArray_destroy(DArray_get(bucket, j));
            }

            DArray_destroy(bucket);
        }

        DArray_destroy(map->buckets);
    }

    free(map);
}

bool Hashmap_set(Hashmap *map, void *key, void *data)
{
    check(map != NULL, "Map cannot be NULL");
    check(map->buckets != NULL, "Map buckets cannot be NULL");

    int index = Hashmap_findBucketIndex(map, key);
    check(index >= 0, "Invalid index received from Hashmap_findBucketIndex");

    DArray *bucket = DArray_get(map->buckets, index);
    if (!bucket)
    {
        bucket = DArray_create(sizeof(void*), 5);
        DArray_set(map->buckets, index, bucket);
    }

    HashmapNode *node = HashmapNode_create(key, data);
    check_mem(node);

    DArray_push(bucket, node);

    return true;

error:
    return false;
}

void *Hashmap_get(Hashmap *map, void *key)
{
    check(map != NULL, "Map cannot be NULL");
    check(map->buckets != NULL, "Map buckets cannot be NULL");

    uint32_t index = Hashmap_findBucketIndex(map, key);

    DArray *bucket = DArray_get(map->buckets, index);
    check(bucket != NULL, "Didn't find bucket for key");

    for (uint32_t i = 0; i < DArray_count(bucket); ++i)
    {
        HashmapNode *node = DArray_get(bucket, i);
        check(node != NULL, "DArray_get returned empty node");

        if (node->key == key)
        {
            return node->data;
        }
    }

error: // fallthrough
    return NULL;
}

bool Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb)
{
    check(map != NULL, "map cannot be NULL");
    check(map->buckets != NULL, "map buckets cannot be NULL");

    bool callbackResult = false;

    for (uint32_t i = 0; i < DArray_count(map->buckets); ++i)
    {
        DArray *bucket = DArray_get(map->buckets, i);
        if (bucket == NULL) continue;

        for (uint32_t j = 0; j < DArray_count(bucket); ++j)
        {
            HashmapNode *node = DArray_get(bucket, j);

            callbackResult = traverse_cb(node);
            check(callbackResult == true,
                  "Traverse callback returned false");
        }
    }

    return true;

error:
    return false;
}

void *Hashmap_delete(Hashmap *map, void *key)
{
    check(map != NULL, "map cannot be NULL");
    check(map->buckets != NULL, "map buckets cannot be NULL");

    uint32_t index = Hashmap_findBucketIndex(map, key);

    DArray *bucket = DArray_get(map->buckets, index);
    check(bucket != NULL, "Didn't find bucket for key");

    for (uint32_t i = 0; i < DArray_count(bucket); ++i)
    {
        HashmapNode *node = DArray_get(bucket, i);
        check(node != NULL, "DArray_get returned empty node");

        log_info("iteration %u", i);
        if (node->key == key)
        {
            DArray_remove(bucket, i);
            return node->data;
        }
    }

error: // fallthrough
    return NULL;
}

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring)a, (bstring)b);
}

/**
 * Simple Bob Jenkins's hash algorithm taken from wikipedia
 */
static uint32_t default_hash(void* key)
{
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

static inline int Hashmap_findBucketIndex(Hashmap *map, void *key)
{
    check(map != NULL, "Hashmap cannot be NULL at this point");
    check(map->hash != NULL, "Hashmap hash function cannot be NULL at this point");
    check(map->buckets != NULL, "Hashmap bucekts cannot be NULL at this point");

    uint32_t hash = map->hash(key);
    uint32_t index = hash % DArray_count(map->buckets);

    return index;
error:
    assert(false); // this is an error in the library logic. Fail fast
    return -1;
}

static inline HashmapNode *HashmapNode_create(void *key, void *value)
{
    HashmapNode *node = malloc(sizeof(HashmapNode));
    check_mem(node);

    node->key = key;
    node->data = value;

    return node;

error:
    return NULL;
}
