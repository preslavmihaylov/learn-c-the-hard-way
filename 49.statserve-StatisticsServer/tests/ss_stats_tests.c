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
        rc = ss_stats_add(NULL, bfromcstr("pesho"));
        mu_assert(rc != 0, "ss_stats_add should fail when stats is NULL");
    }

    {
        rc = ss_stats_add(stats, NULL);
        mu_assert(rc != 0, "ss_stats_add should fail when key is NULL");
    }

    {
        SS_Stats *brokenStats = ss_stats_create();
        brokenStats->data = NULL;
        rc = ss_stats_add(brokenStats, bfromcstr("pesho"));
        mu_assert(rc != 0, "ss_stats_add should fail when stats is broken");
    }

    {
        ss_stats_add(stats, bfromcstr("pesho"));
        mu_assert(Hashmap_get(stats->data, bfromcstr("pesho")) != NULL, "Failed to add statistics");
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_add);

    return NULL;
}

RUN_TESTS(all_tests);
