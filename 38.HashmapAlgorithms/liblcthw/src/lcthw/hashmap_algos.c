#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>

#define FNV_OFFSET_BASIS 2166136261
#define FNV_PRIME 16777619

uint32_t Hashmap_fnv1a_hash(void *data)
{
	bstring str = (bstring)data;
	uint32_t hash = FNV_OFFSET_BASIS;

	for (int i = 0; i < blength(str); ++i)
	{
		hash = hash ^ bchar(str, i);
		hash = hash * FNV_PRIME;
	}

	return hash;
}

uint32_t Hashmap_adler32_hash(void *data)
{
	// TODO:
	return 0;
}

uint32_t Hashmap_djb_hash(void *data)
{
	// TODO:
	return 0;
}
