#include <lcthw/bstree.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>
#include <assert.h>

typedef enum
{
    BSTNodeChild_LEFT,
    BSTNodeChild_RIGHT
} BSTNodeChild;

static int BSTree_default_compare(void *a, void *b);
static int BSTree_destroy_cb(BSTNode *node);
static int BSTNode_traverse(BSTNode *node, BSTree_traverse_cb traverse_cb);
static int BSTNode_set(BSTNode *node, void *key, void *value, BSTree_compare compare_cb);
static BSTNode *BSTNode_create(void *key, void *value, BSTNode *parent);
static BSTNode *BSTNode_getNode(BSTNode *node, void *key, BSTree_compare compare_cb);
static void *BSTNode_delete(BSTree *tree, BSTNode *node);
static BSTNode *BSTNode_findRightmostNode(BSTNode *node);
static void BSTNode_assignChild(BSTNode *parent, BSTNode *child, BSTNodeChild childType);
static void BSTNode_replaceParent(BSTree *tree, BSTNode *childNode, BSTNode *newChildNode);

BSTree *BSTree_create(BSTree_compare compare_cb)
{
    BSTree *tree = malloc(sizeof(BSTree));
    check_mem(tree);

    tree->count = 0;
    tree->root = NULL;
    tree->compare_cb =
        compare_cb != NULL ? compare_cb : BSTree_default_compare;

    return tree;

error:
    BSTree_destroy(tree);
    return NULL;
}

void BSTree_destroy(BSTree *tree)
{
    if (tree)
    {
        BSTree_traverse(tree, BSTree_destroy_cb);
        free(tree);
    }
}

int BSTree_set(BSTree *tree, void *key, void *value)
{
    check(tree != NULL, "Map cannot be NULL");

    if (!tree->root)
    {
        tree->root = BSTNode_create(key, value, NULL);
    }
    else
    {
        return BSTNode_set(tree->root, key, value, tree->compare_cb);
    }

    ++tree->count;
    return 0;

error:
    return -1;
}

void *BSTree_get(BSTree *tree, void *key)
{
    if (tree->root)
    {
        BSTNode *node = BSTNode_getNode(tree->root, key, tree->compare_cb);

        return node != NULL ? node->value : NULL;
    }

    return NULL;
}

int BSTree_traverse(BSTree *tree, BSTree_traverse_cb traverse_cb)
{
    check(tree != NULL, "Map cannot be NULL");
    check(traverse_cb != NULL, "Traverse callback cannot be NULL");

    if (tree->root)
    {
        return BSTNode_traverse(tree->root, traverse_cb);
    }
    else
    {
        return 0;
    }

error:
    return -1;
}

void *BSTree_delete(BSTree *tree, void *key)
{
    if (tree->root)
    {
        BSTNode *node = BSTNode_getNode(tree->root, key, tree->compare_cb);
        if (!node) return NULL;

        return BSTNode_delete(tree, node);
    }

    --tree->count;
    return NULL;
}

static int BSTree_default_compare(void *a, void *b)
{
    return bstrcmp((bstring)a, (bstring)b);
}

static int BSTree_destroy_cb(BSTNode *node)
{
    free(node);
    return 0;
}

static int BSTNode_traverse(BSTNode *node, BSTree_traverse_cb traverse_cb)
{
    check(node != NULL, "Node cannot be NULL");
    check(traverse_cb != NULL, "Traverse callback cannot be NULL");
    int rc = 0;

    if (node->left)
    {
        rc = BSTNode_traverse(node->left, traverse_cb);
        if (rc != 0) return rc;
    }

    if (node->right)
    {
        rc = BSTNode_traverse(node->right, traverse_cb);
        if (rc != 0) return rc;
    }

    return traverse_cb(node);

error: // fallthrough
    return -1;
}

static int BSTNode_set(BSTNode *node, void *key, void *value, BSTree_compare compare_cb)
{
    check(node != NULL, "Node cannot be NULL");

    int compareResult = compare_cb(key, node->key);
    if (compareResult == 0)
    {
        node->value = value;
    }
    else if (compareResult > 0)
    {
        if (node->right != NULL)
        {
            return BSTNode_set(node->right, key, value, compare_cb);
        }
        else
        {
            node->right = BSTNode_create(key, value, node);
        }
    }
    else
    {
        if (node->left != NULL)
        {
            return BSTNode_set(node->left, key, value, compare_cb);
        }
        else
        {
            node->left = BSTNode_create(key, value, node);
        }
    }

    return 0;

error:
    return -1;
}

static BSTNode *BSTNode_create(void *key, void *value, BSTNode *parent)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    check_mem(node);

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    return node;

error:
    return NULL;
}

static BSTNode *BSTNode_getNode(BSTNode *node, void *key, BSTree_compare compare_cb)
{
    check(node != NULL, "Node cannot be NULL");
    check(compare_cb != NULL, "Compare callback cannot be NULL");

    int compareResult = compare_cb(key, node->key);
    if (compareResult == 0)
    {
        return node;
    }
    else if (compareResult > 0)
    {
        return BSTNode_getNode(node->right, key, compare_cb);
    }
    else
    {
        return BSTNode_getNode(node->left, key, compare_cb);
    }

error:
    return NULL;
}

static void *BSTNode_delete(BSTree *tree, BSTNode *node)
{
    check(tree != NULL, "Map cannot be NULL");
    check(node != NULL, "Node cannot be NULL");

    void *value = node->value;
    if (node->left && node->right)
    {
        BSTNode *nodeToSwap = BSTNode_findRightmostNode(node->left);
        assert(nodeToSwap->parent);

        BSTNode_replaceParent(tree, nodeToSwap, nodeToSwap->left);

        node->key = nodeToSwap->key;
        node->value = nodeToSwap->value;

        free(nodeToSwap);
    }
    else if (node->left)
    {
        BSTNode_replaceParent(tree, node, node->left);
        free(node);
    }
    else
    {
        BSTNode_replaceParent(tree, node, node->right);
        free(node);
    }

    return value;

error:
    return NULL;
}

static BSTNode *BSTNode_findRightmostNode(BSTNode *node)
{
    if (node->right)
    {
        return BSTNode_findRightmostNode(node->right);
    }
    else
    {
        return node;
    }
}

static void BSTNode_assignChild(BSTNode *parent, BSTNode *child, BSTNodeChild childType)
{
    if (parent)
    {
        if (childType == BSTNodeChild_LEFT)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }

    if (child)
    {
        child->parent = parent;
    }
}

static void BSTNode_replaceParent(BSTree *tree, BSTNode *childNode, BSTNode *newChildNode)
{
    check(tree != NULL, "Map cannot be NULL");
    check(childNode != NULL, "Child node cannot be NULL");

    if (childNode->parent)
    {
        BSTNodeChild childType =
            childNode->parent->left == childNode ? BSTNodeChild_LEFT : BSTNodeChild_RIGHT;

        BSTNode_assignChild(childNode->parent, newChildNode, childType);
    }
    else
    {
        tree->root = newChildNode;

        if (newChildNode)
        {
            newChildNode->parent = NULL;
        }
    }

error: // fallthrough
    return;
}
