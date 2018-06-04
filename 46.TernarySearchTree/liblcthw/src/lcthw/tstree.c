#include <lcthw/tstree.h>

static TSTree *TSTree_insert_base(TSTree *root, TSTree *node, const char *key, size_t len, void *value)
{
    return NULL;
}

TSTree *TSTree_insert(TSTree *root, const char *key, size_t len, void *value)
{
    return NULL;
}

void *TSTree_search(TSTree *root, const char *key, size_t len)
{
    return NULL;
}

void *TSTree_search_prefix(TSTree *root, const char *key, size_t len)
{
    return NULL;
}

void TSTree_traverse(TSTree *root, TSTree_traverse_cb cb, void *data)
{
}

void TSTree_destroy(TSTree *root)
{
}
