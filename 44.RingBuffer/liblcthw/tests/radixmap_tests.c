#include "minunit.h"
#include <lcthw/radixmap.h>
#include <time.h>
#include <stdbool.h>

static bool make_random(RadixMap *map)
{
	size_t i = 0;

	for (i = 0; i < map->capacity - 1; i++)
	{
		uint32_t key = (uint32_t)(rand() | (rand() << 16));
		check(RadixMap_add(map, key, i) == 0, "Failed to add key %u", key);
	}

	return true;

error:
	return false;
}

static bool check_order(RadixMap *map)
{
	RMElement d1, d2;
	uint32_t i = 0;
	
	for (i = 0; map->count > 0 && i < map->count - 1; ++i)
	{
		d1 = map->contents[i];
		d2 = map->contents[i + 1];

		if (d1.data.key > d2.data.key)
		{
			debug("FAIL:i=%u, key=%u, value=%u, equals max? %d\n",
				i,
				d1.data.key,
				d1.data.value,
				d2.data.key == UINT32_MAX);

			return false;
		}
	}

	return true;
}

static bool test_search(RadixMap *map)
{
	uint32_t i = 0;
	RMElement *d = NULL;
	RMElement *found = NULL;

	for (i = map->count / 2; i < map->count; i++)
	{
		d = &map->contents[i];

		found = RadixMap_find(map, d->data.key);
		check(found != NULL, "Didn't find %u at %u", d->data.key, i);
		check(found->data.key == d->data.key, 
			"Got the wrong result: %p:%u looking for %u at %u",
			found,
			found->data.key,
			d->data.key,
			i);
	}

	return true;

error:
	return false;
}

static char *test_operations()
{
	size_t N = 200;

	RadixMap *map = RadixMap_create(N);
	mu_assert(map != NULL, "Failed to make the map");
	mu_assert(make_random(map), "Didn't make a random fake radix map");

	RadixMap_sort(map);
	mu_assert(check_order(map),
		"Failed to properly sort the RadixMap");

	mu_assert(test_search(map), "failed the search test.");
	mu_assert(check_order(map), 
		"RadixMap didn't stay sorted after search");
	
	while (map->count > 0)
	{
		RMElement *el = RadixMap_find(
			map, map->contents[map->count / 2].data.key);

		mu_assert(el != NULL, "Should get a result");

		size_t old_count = map->count;

		mu_assert(RadixMap_delete(map, el) == 0, "Didn't delete it");
		mu_assert(old_count - 1 == map->count, "Wrong size after delete");

		mu_assert(check_order(map), 
				  "RadixMap didn't stay sorted after delete");
	}

	RadixMap_destroy(map);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	srand(time(NULL));

	mu_run_test(test_operations);

	return NULL;
}

RUN_TESTS(all_tests);
