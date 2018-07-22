#ifndef _SS_IO
#define _SS_IO

#include <lcthw/bstrlib.h>
#include <stdint.h>

int ss_io_store(bstring filename, void *data, uint32_t size);
int ss_io_load(bstring filename, void *buffer, uint32_t size);

#endif // _SS_IO
