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
    else
    {
        if (len == 1)
        {
            check(node->value == NULL, "Duplicates are not allowed");
            node->value = value;
        }
        else
        {
            node->equal = TSTree_insert_base(node->equal, key+1, len-1, value);
        }
    }

    return node;

error:
    return NULL;
}

TSTree *TSTree_insert(TSTree *root, const char *key, size_t len, void *value)
{
    check(key != NULL, "Key cannot be NULL");
    check(len > 0, "Length must be positive");

    return TSTree_insert_base(root, key, len, value);
   
error:
    return NULL;
}

void *TSTree_search(TSTree *root, const char *key, size_t len)
{
    check(root != NULL, "node cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(len > 0, "length must be positive");

    TSTree *node = root;
    (void)node;

    if (*key < node->splitchar)
    {
        return TSTree_search(root->left, key, len);
    }
    else if (*key > node->splitchar)
    {
        return TSTree_search(root->right, key, len);
    }
    else
    {
        if (len > 1)
            return TSTree_search(root->equal, key+1, len-1);

        return node->value;
    }

error: // fallthrough
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
