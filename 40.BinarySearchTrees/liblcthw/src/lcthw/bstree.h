#ifndef LCTHW_BSTREE_H
#define LCTHW_BSTREE_H

#include <stdlib.h>
#include <lcthw/bstrlib.h>

typedef int (*BSTree_compare) (void *a, void *b);

typedef struct BSTNode
{
	void *key;
	void *value;

	struct BSTNode *left;
	struct BSTNode *right;
	struct BSTNode *parent;
} BSTNode;

typedef struct BSTree
{
	int count;
	BSTree_compare compare_cb;
	BSTNode *root;
} BSTree;

typedef int (*BSTree_traverse_cb) (BSTNode *node);

BSTree *BSTree_create(BSTree_compare compare_cb);
void BSTree_destroy(BSTree *tree);

int BSTree_set(BSTree *tree, void *key, void *value);
void *BSTree_get(BSTree *tree, void *key);

int BSTree_traverse(BSTree *tree, BSTree_traverse_cb traverse_cb);

void *BSTree_delete(BSTree *tree, void *key);

#endif // LCTHW_BSTREE_H
