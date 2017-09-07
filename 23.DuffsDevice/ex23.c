#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>

#define CHARS_CNT 100000

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for (i = 0; i < count; ++i)
    {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
    int n = (count + 7) / 8;

    switch (count % 8)
    {
        case 0:
            do {
              *to++ = *from++;
                case 7:
              *to++ = *from++;
                case 6:
              *to++ = *from++;
                case 5:
              *to++ = *from++;
                case 4:
              *to++ = *from++;
                case 3:
              *to++ = *from++;
                case 2:
              *to++ = *from++;
                case 1:
              *to++ = *from++;
            } while (--n > 0);
    }

    return count;
}

int zeds_device(char *from, char *to, int count)
{
    int n = (count + 7) / 8;

    switch (count % 8)
    {
        case 0:
again:        *to++ = *from++;
                case 7:
              *to++ = *from++;
                case 6:
              *to++ = *from++;
                case 5:
              *to++ = *from++;
                case 4:
              *to++ = *from++;
                case 3:
              *to++ = *from++;
                case 2:
              *to++ = *from++;
                case 1:
              *to++ = *from++;
              if (--n > 0) goto again;
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; ++i)
    {
        if (data[i] != expects) 
        {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char from[CHARS_CNT] = { 'a' };
    char to[CHARS_CNT] = { 'c' };
    int rc = 0;
    clock_t begin;
    clock_t end;
    double timeSpent;

    memset(from, 'x', CHARS_CNT);
    memset(to, 'y', CHARS_CNT);
    check(valid_copy(to, CHARS_CNT, 'y'), "Not initialized right.");

    begin = clock();
    rc = normal_copy(from, to, CHARS_CNT);
    end = clock();
    timeSpent = ((double)(end - begin)) / CLOCKS_PER_SEC; 
    log_info("Normal copy time: %f", timeSpent);

    check(rc == CHARS_CNT, "Normal copy failed: %d", rc);
    check(valid_copy(to, CHARS_CNT, 'x'), "Normal copy failed.");

    memset(to, 'y', CHARS_CNT);
    
    begin = clock();
    rc = duffs_device(from, to, CHARS_CNT);
    end = clock();
    timeSpent = ((double)(end - begin)) / CLOCKS_PER_SEC; 
    log_info("Duff's device time: %f", timeSpent);
    
    check(rc == CHARS_CNT, "Duff's device failed: %d", rc);
    check(valid_copy(to, CHARS_CNT, 'x'), "Duff's device failed copy.");

    memset(to, 'y', CHARS_CNT);
    
    begin = clock();
    rc = zeds_device(from, to, CHARS_CNT);
    end = clock();
    timeSpent = ((double)(end - begin)) / CLOCKS_PER_SEC; 
    log_info("Zed's device time: %f", timeSpent);
    
    check(rc == CHARS_CNT, "Zed's device failed: %d", rc);
    check(valid_copy(to, CHARS_CNT, 'x'), "Zed's device failed copy.");

    return 0;
error:
    return 1;
}
