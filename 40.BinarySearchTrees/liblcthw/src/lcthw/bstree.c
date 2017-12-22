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
static void *BSTNode_delete(BSTree *map, BSTNode *node);
static BSTNode *BSTNode_findRightmost(BSTNode *node);
static void BSTNode_assignChild(BSTNode *parent, BSTNode *child, BSTNodeChild childType);
static void BSTNode_setParent(BSTree *map, BSTNode *childNode, BSTNode *newChildNode);

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
	return NULL;
}

void BSTree_destroy(BSTree *map)
{
	if (map)
	{
		BSTree_traverse(map, BSTree_destroy_cb);
		free(map);
	}
}

int BSTree_set(BSTree *map, void *key, void *value)
{
	check(map != NULL, "Map cannot be NULL");

	if (!map->root)
	{
		map->root = BSTNode_create(key, value, NULL);
	}
	else
	{
		return BSTNode_set(map->root, key, value, map->compare_cb);
	}

	return 0;

error:
	return -1;
}

void *BSTree_get(BSTree *map, void *key)
{
	if (map->root)
	{
		BSTNode *node = BSTNode_getNode(map->root, key, map->compare_cb);

		return node != NULL ? node->value : NULL;
	}

	return NULL;
}

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb)
{
	check(map != NULL, "Map cannot be NULL");
	check(traverse_cb != NULL, "Traverse callback cannot be NULL");

	if (map->root)
	{
		return BSTNode_traverse(map->root, traverse_cb);
	}
	else
	{
		return 0;
	}

error:
	return -1;
}

void *BSTree_delete(BSTree *map, void *key)
{
	if (map->root)
	{
		BSTNode *node = BSTNode_getNode(map->root, key, map->compare_cb);
		if (!node) return NULL;

		return BSTNode_delete(map, node);
	}

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
		if (node->right)
		{
			return BSTNode_getNode(node->right, key, compare_cb);
		}
	}
	else
	{
		if (node->left)
		{
			return BSTNode_getNode(node->left, key, compare_cb);
		}
	}

error:
	return NULL;
}

static void *BSTNode_delete(BSTree *map, BSTNode *node)
{
	check(map != NULL, "Map cannot be NULL");
	check(node != NULL, "Node cannot be NULL");

	void *value = node->value;
	if (node->left && node->right)
	{
		BSTNode *nodeToSwap = BSTNode_findRightmost(node->left);
		assert(nodeToSwap->parent);

		node->key = nodeToSwap->key;
		node->value = nodeToSwap->value;

		BSTNode_setParent(map, nodeToSwap, nodeToSwap->left);
		free(nodeToSwap);
	}
	else if (node->left)
	{
		BSTNode_setParent(map, node, node->left);
		free(node);
	}
	else
	{
		BSTNode_setParent(map, node, node->right);
		free(node);
	}

	return value;

error:
	return NULL;
}

static BSTNode *BSTNode_findRightmost(BSTNode *node)
{
	if (node->right)
	{
		return BSTNode_findRightmost(node->right);
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

static void BSTNode_setParent(BSTree *map, BSTNode *childNode, BSTNode *newChildNode)
{
	check(map != NULL, "Map cannot be NULL");
	check(childNode != NULL, "Child node cannot be NULL");

	if (childNode->parent)
	{
		BSTNodeChild childType =
			childNode->parent->left == childNode ? BSTNodeChild_LEFT : BSTNodeChild_RIGHT;

		BSTNode_assignChild(childNode->parent, newChildNode, childType);
	}
	else
	{
		map->root = newChildNode;

		if (newChildNode)
		{
			newChildNode->parent = NULL;
		}
	}

error: // fallthrough
	return;
}
