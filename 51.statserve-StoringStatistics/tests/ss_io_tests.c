#include "minunit.h"
#include <ss_io.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct TestData {
    char strDat[10];
    int intDat;
    char charDat;
    float floatDat;
} TestData;

bool tstDataIsEq(TestData first, TestData second)
{
    return strcmp(first.strDat, second.strDat) == 0 && first.floatDat == second.floatDat &&
           first.intDat == second.intDat && first.charDat == second.charDat;
}

static char *ioFilename = "/tmp/asd";
static TestData tstDat = { .strDat = "Hello", .intDat = 1, .charDat = 'c', .floatDat = 3.14f };

char *test_store()
{
    bstring filename = bfromcstr(ioFilename);
    bstring expectedFilename = bfromcstr("iocadjma");

    ss_io_store(filename, (void *)&tstDat, sizeof(tstDat));

    char *charFilename = bdata(expectedFilename);
    mu_assert(access(charFilename, F_OK) >= 0, "File does not exist after ss_io_store");

    TestData storedTstData;
    FILE *fp = fopen(charFilename, "rb");
    mu_assert(fp != NULL, "Failed to open file after ss_io_store");

    fread(&storedTstData, sizeof(storedTstData), 1, fp);
    mu_assert(tstDataIsEq(storedTstData, tstDat) == true, "Stored test data is not valid after ss_io_store");

    fclose(fp);

    return NULL;
}

char *test_load()
{
    int rc = 0;
    bstring filename = bfromcstr(ioFilename);

    TestData expectedTstData = tstDat;
    TestData actualTstData;
    bzero(&actualTstData, sizeof(actualTstData));

    ss_io_load(filename, &actualTstData, sizeof(actualTstData));
    mu_assert(tstDataIsEq(expectedTstData, actualTstData) == true, "Loaded test data is not valid after ss_io_load");

    rc = remove(bdata(filename));
    mu_assert(rc == 0, "Failed to delete file after ss_io_load test");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_store);
    mu_run_test(test_load);

    return NULL;
}

RUN_TESTS(all_tests);
