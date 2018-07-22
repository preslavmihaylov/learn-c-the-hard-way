#include <ss_io.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcthw/dbg.h>
#include <lcthw/hashmap_algos.h>

#define BYTE_LENGTH 8
#define NIBBLE_LENGTH 4

static char *ss_io_strhash(uint32_t hash)
{
    uint8_t currentByte = 0;
    char *result = calloc(32 / NIBBLE_LENGTH, sizeof(char));

    for (size_t i = 0; i < (32 / NIBBLE_LENGTH); i++)
    {
        currentByte = hash >> (i * NIBBLE_LENGTH);
        uint8_t currentNibble = currentByte & 0x0F;

        result[i] = 'a' + currentNibble;
    }

    return result;
}

int ss_io_store(bstring filename, void *data, uint32_t size)
{
    uint32_t hash = Hashmap_adler32_hash(filename);
    char *filenameHash = ss_io_strhash(hash);

    FILE *fp = fopen(filenameHash, "w+");
    check(fp != NULL, "failed to open file");

    size_t rc = fwrite(data, size, 1, fp);
    check(rc == 1, "Failed to store data in %s", bdata(filename));

    fclose(fp);
    if (filenameHash) free(filenameHash);

    return 0;

error: // fallthrough
    if (filenameHash) free(filenameHash);

    return -1;
}

int ss_io_load(bstring filename, void *buffer, uint32_t size)
{
    uint32_t hash = Hashmap_adler32_hash(filename);
    char *filenameHash = ss_io_strhash(hash);

    FILE *fp = fopen(filenameHash, "r");
    check(fp != NULL, "failed to open file");

    int rc = fread(buffer, size, 1, fp);
    check(rc == 1, "failed to read file on ss_io_load");

    if (filenameHash) free(filenameHash);

    return 0;

error: // fallthrough
    if (filenameHash) free(filenameHash);

    return -1;
}

