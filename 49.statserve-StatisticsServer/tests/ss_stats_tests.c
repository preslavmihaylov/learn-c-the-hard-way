#include "minunit.h"
#include <ss_stats.h>

char *test_create()
{
    SS_Stats *stats = ss_stats_create();
    mu_assert(stats != NULL, "Failed to create stats");
    mu_assert(stats->data != NULL, "Failed to create stats hashmap");

    return NULL;
}

char *test_add()
{
    int rc;
    SS_Stats *stats = ss_stats_create();
    {
        rc = ss_stats_add(NULL, bfromcstr("sample"));
        mu_assert(rc != 0, "ss_stats_add should fail when stats is NULL");
    }

    {
        rc = ss_stats_add(stats, NULL);
        mu_assert(rc != 0, "ss_stats_add should fail when key is NULL");
    }

    {
        SS_Stats *brokenStats = ss_stats_create();
        brokenStats->data = NULL;
        rc = ss_stats_add(brokenStats, bfromcstr("sample"));
        mu_assert(rc != 0, "ss_stats_add should fail when stats is broken");
    }

    {
        ss_stats_add(stats, bfromcstr("sample"));
        mu_assert(Hashmap_get(stats->data, bfromcstr("sample")) != NULL, "Failed to add statistics");
    }

    return NULL;
}

char *test_sample()
{
    int rc;
    SS_Stats *stats = ss_stats_create();
    bstring str = bfromcstr("sample");

    {
        rc = ss_stats_sample(NULL, str, 10);
        mu_assert(rc != 0, "expected to fail ss_stats_sample when stats are NULL");
    }

    {
        rc = ss_stats_sample(stats, NULL, 10);
        mu_assert(rc != 0, "expected to fail ss_stats_sample when key is NULL");
    }

    {
        SS_Stats *brokenStats = ss_stats_create();
        brokenStats->data = NULL;

        rc = ss_stats_sample(brokenStats, str, 10);
        mu_assert(rc != 0, "expected to fail ss_stats_sample when stats are broken");
    }

    {
        rc = ss_stats_sample(stats, str, 10);
        mu_assert(rc != 0, "expected to fail ss_stats_sample when key does not exist");
    }

    {
        ss_stats_add(stats, str);
        rc = ss_stats_sample(stats, str, 10);
        mu_assert(rc == 0, "ss_stats_sample failed unexpectedly");
        Stats *currStats = Hashmap_get(stats->data, str);
        mu_assert(currStats->sum == 10, "ss_stats_sample failed to add sample correctly");
    }

    return NULL;
}

char *test_mean()
{
    int rc;
    double mean = 0;
    SS_Stats *stats = ss_stats_create();
    bstring str = bfromcstr("sample");
    (void)stats;

    {
        rc = ss_stats_mean(NULL, str, &mean);
        mu_assert(rc != 0, "ss_stats_mean should not pass when stats is NULL");
    }

    {
        rc = ss_stats_mean(stats, NULL, &mean);
        mu_assert(rc != 0, "ss_stats_mean should not pass when key is NULL");
    }

    {
        rc = ss_stats_mean(stats, str, &mean);
        mu_assert(rc != 0, "ss_stats_mean should not pass when key does not exist in stats");
    }

    {
        rc = ss_stats_add(stats, str);
        mu_assert(rc == 0, "ss_stats_add unexpectedly failed");

        rc = ss_stats_mean(stats, str, &mean);
        mu_assert(rc != 0, "ss_stats_mean of 0 elements is expected to be invalid");

        rc = ss_stats_sample(stats, str, 10);
        mu_assert(rc == 0, "ss_stats_sample unexpectedly failed");

        rc = ss_stats_mean(stats, str, &mean);
        mu_assert(mean == 10, "ss_stats_mean should be 10 given set [ 10 ]");

        rc = ss_stats_sample(stats, str, 15);
        mu_assert(rc == 0, "ss_stats_sample unexpectedly failed");

        rc = ss_stats_mean(stats, str, &mean);
        mu_assert(mean == 12.5, "ss_stats_mean should be 12.5 given set [ 10, 15 ]");

        rc = ss_stats_sample(stats, str, 5);
        mu_assert(rc == 0, "ss_stats_sample unexpectedly failed");

        rc = ss_stats_mean(stats, str, &mean);
        mu_assert(mean == 10, "ss_stats_mean should be 10 given set [ 10, 15, 5 ]");
    }

    return NULL;
}

char *test_dump()
{
    int rc;
    SS_Stats *stats = ss_stats_create();
    bstring str = bfromcstr("sample");

    {
        Stats *dumpedStats = ss_stats_dump(NULL, str);
        mu_assert(dumpedStats == NULL, "expected ss_stats_dump to return NULL when stats are NULL");
    }

    {
        Stats *dumpedStats = ss_stats_dump(stats, NULL);
        mu_assert(dumpedStats == NULL, "expected ss_stats_dump to return NULL when key is non-existent");
    }

    {
        SS_Stats *brokenStats = ss_stats_create();
        brokenStats->data = NULL;

        Stats *dumpedStats = ss_stats_dump(brokenStats, str);
        mu_assert(dumpedStats == NULL, "expected ss_stats_dump to return NULL when structure is broken");
    }

    {
        Stats *dumpedStats = ss_stats_dump(stats, str);
        mu_assert(dumpedStats == NULL, "expected ss_stats_dump to return NULL when key is non-existent");
    }

    {
        rc = ss_stats_add(stats, str);
        mu_assert(rc == 0, "ss_stats_add failed unexpectedly");

        ss_stats_sample(stats, str, 10);
        mu_assert(rc == 0, "ss_stats_sample failed unexpectedly");

        Stats *currStats = Hashmap_get(stats->data, str);
        Stats *dumpedStats = ss_stats_dump(stats, str);
        mu_assert(currStats == dumpedStats, "ss_stats_dump returned wrong results");
    }

    return NULL;
}

char *test_delete()
{
    int rc;
    SS_Stats *stats = ss_stats_create();
    bstring str = bfromcstr("sample");

    {
        rc = ss_stats_delete(NULL, str);
        mu_assert(rc != 0, "expected ss_stats_delete to fail when stats are NULL");
    }

    {
        rc = ss_stats_delete(stats, NULL);
        mu_assert(rc != 0, "expected ss_stats_delete to fail when key is NULL");
    }

    {
        rc = ss_stats_delete(stats, str);
        mu_assert(rc != 0, "expected ss_stats_delete to fail when key is not added");
    }

    {
        rc = ss_stats_add(stats, str);
        mu_assert(rc == 0, "ss_stats_add unexpectedly failed");

        Stats *dumpedStats = ss_stats_dump(stats, str);
        mu_assert(dumpedStats != NULL, "dumped stats after add are unexpectedly NULL");

        rc = ss_stats_delete(stats, str);
        mu_assert(rc == 0, "ss_stats_delete unexpectedly failed");

        dumpedStats = ss_stats_dump(stats, str);
        mu_assert(dumpedStats == NULL, "dumped stats after delete are unexpectedly not NULL");
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_add);
    mu_run_test(test_sample);
    mu_run_test(test_mean);
    mu_run_test(test_dump);
    mu_run_test(test_delete);

    return NULL;
}

RUN_TESTS(all_tests);
