#ifndef LCTHW_HASHMAP_ALGOS_H
#define LCTHW_HASHMAP_ALGOS_H

#include <stdint.h>

uint32_t Hashmap_fnv1a_hash(void *data);
uint32_t Hashmap_adler32_hash(void *data);
uint32_t Hashmap_djb_hash(void *data);

#endif // LCTHW_HASHMAP_ALGOS_H
