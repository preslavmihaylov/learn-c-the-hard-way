#include <lcthw/tstree.h>

static TSTree *TSTree_insert_base(TSTree *node, const char *key, size_t len, void *value)
{
    if (node == NULL)
    {
        node = calloc(1, sizeof(TSTree));
        node->splitchar = *key;
    }

    if (*key < node->splitchar)
    {
        node->left = TSTree_insert_base(node->left, key, len, value);
    }
    else if (*key > node->splitchar)
    {
        node->right = TSTree_insert_base(node->right, key, len, value);
    }
    else if (len > 1)
    {
        node->equal = TSTree_insert_base(node->equal, key+1, len-1, value);
    }
    else
    {
        check(node->value == NULL, "Duplicates are not allowed");
        node->value = value;
    }

    return node;

error:
    return NULL;
}

TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value)
{
    check(key != NULL, "Key cannot be NULL");
    check(len > 0, "Length must be positive");

    return TSTree_insert_base(node, key, len, value);

error:
    return NULL;
}

void *TSTree_search(const TSTree *node, const char *key, size_t len)
{
    check(key != NULL, "key cannot be NULL");
    check(len > 0, "length must be positive");

    if (node == NULL) return NULL;

    if (*key < node->splitchar)
    {
        return TSTree_search(node->left, key, len);
    }
    else if (*key > node->splitchar)
    {
        return TSTree_search(node->right, key, len);
    }
    else if (len > 1)
    {
        return TSTree_search(node->equal, key+1, len-1);
    }

    return node->value;

error: // fallthrough
    return NULL;
}

void *TSTree_search_prefix(const TSTree *node, const char *key, size_t len)
{
    check(key != NULL, "Key cannot be NULL");
    check(len > 0, "Length must be positive");

    if (node == NULL) return NULL;

    if (*key < node->splitchar)
    {
        return TSTree_search_prefix(node->left, key, len);
    }
    else if (*key > node->splitchar)
    {
        return TSTree_search_prefix(node->right, key, len);
    }
    else if (len > 1)
    {
        return TSTree_search_prefix(node->equal, key+1, len-1);
    }

    while (node && node->value == NULL)
    {
        node = node->equal;
    }

    return node->value;

error:
    return NULL;
}

void TSTree_traverse(TSTree *node, TSTree_traverse_cb cb, void *data)
{
    check(node != NULL, "Node cannot be NULL");
    check(cb != NULL, "callback cannot be NULL");

    if (node->left)
    {
        TSTree_traverse(node->left, cb, data);
    }

    if (node->right)
    {
        TSTree_traverse(node->right, cb, data);
    }

    if (node->equal)
    {
        TSTree_traverse(node->equal, cb, data);
    }

    if (node->value)
    {
        cb(node->value, data);
    }

error: // fallthrough
    return;
}

void TSTree_destroy(TSTree *node)
{
    if (node->left)
    {
        TSTree_destroy(node->left);
    }

    if (node->right)
    {
        TSTree_destroy(node->right);
    }

    if (node->equal)
    {
        TSTree_destroy(node->equal);
    }

    free(node);
}

