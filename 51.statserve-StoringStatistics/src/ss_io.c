#include <ss_io.h>
#include <stdio.h>
#include <lcthw/dbg.h>

void ss_io_store(bstring filename, void *data, uint32_t size)
{
    FILE *fp = fopen(bdata(filename), "w+");
    check(fp != NULL, "failed to open file");

    size_t rc = fwrite(data, size, 1, fp);
    check(rc == 1, "Failed to store data in %s", bdata(filename));

    fclose(fp);

error: // fallthrough
    return;
}

void ss_io_load(bstring filename, void *buffer, uint32_t size)
{

}

