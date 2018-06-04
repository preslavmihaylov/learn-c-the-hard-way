#ifndef _TS_TREE_H
#define _TS_TREE_H

#include <stdlib.h>
#include <lcthw/darray.h>

typedef struct TSTree {
    char splitchar;
    struct TSTree *left;
    struct TSTree *equal;
    struct TSTree *right;
    void *value;
} TSTree;

TSTree *TSTree_insert(TSTree *root, const char *key, size_t len, void *value);

void *TSTree_search(TSTree *root, const char *key, size_t len);
void *TSTree_search_prefix(TSTree *root, const char *key, size_t len);

typedef void (*TSTree_traverse_cb)(void *value, void *data);
void TSTree_traverse(TSTree *root, TSTree_traverse_cb cb, void *data);

void TSTree_destroy(TSTree *root);

#endif
