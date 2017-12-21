#include <lcthw/bstree.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>

static int BSTree_default_compare(void *a, void *b);

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
	// TODO:
}

int BSTree_set(BSTree *map, void *key, void *value)
{
	// TODO:
	return 0;
}

void *BSTree_get(BSTree *map, void *key)
{
	// TODO:
	return NULL;
}

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb)
{
	// TODO:
	return 0;
}

void *BSTree_delete(BSTree *map, void *key)
{
	// TODO:
	return NULL;
}

static int BSTree_default_compare(void *a, void *b)
{
	return bstrcmp((bstring)a, (bstring)b);
}
