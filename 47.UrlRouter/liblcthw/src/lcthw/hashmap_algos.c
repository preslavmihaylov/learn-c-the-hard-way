#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>

const uint32_t FNV_OFFSET_BASIS = 2166136261U;
const uint32_t FNV_PRIME = 16777619U;

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

const uint32_t MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
	bstring str = (bstring)data;

	uint32_t lo_byte = 1;
	uint32_t hi_byte = 0;

	for (int i = 0; i < blength(str); ++i)
	{
		lo_byte = (lo_byte + bchar(str, i)) % MOD_ADLER;
		hi_byte = (hi_byte + lo_byte) % MOD_ADLER;
	}

	return ((hi_byte << 16) | lo_byte);
}

uint32_t Hashmap_djb_hash(void *data)
{
	bstring str = (bstring)data;
	uint32_t hash = 5381;

	for (int i = 0; i < blength(str); ++i)
	{
		/* hash * 33 + c */
		hash = ((hash << 5) + hash) + bchar(str, i);
	}

	return hash;
}
