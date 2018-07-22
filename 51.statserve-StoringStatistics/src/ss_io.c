#include <ss_io.h>
#include <stdio.h>
#include <lcthw/dbg.h>

int ss_io_store(bstring filename, void *data, uint32_t size)
{
    FILE *fp = fopen(bdata(filename), "w+");
    check(fp != NULL, "failed to open file");

    size_t rc = fwrite(data, size, 1, fp);
    check(rc == 1, "Failed to store data in %s", bdata(filename));

    fclose(fp);

    return 0;

error: // fallthrough
    return -1;
}

int ss_io_load(bstring filename, void *buffer, uint32_t size)
{
    FILE *fp = fopen(bdata(filename), "r");
    check(fp != NULL, "failed to open file");

    int rc = fread(buffer, size, 1, fp);
    check(rc == 1, "failed to read file on ss_io_load");

    return 0;

error: // fallthrough
    return -1;
}

