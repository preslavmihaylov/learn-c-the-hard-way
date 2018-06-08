#include "minunit.h"
#include <lcthw/stats.h>
#include <math.h>

const int NUM_SAMPLES = 10;
double samples[] =
{
    6.1061334, 9.6783204, 1.2747090, 8.2395131, 0.3333483,
    6.9755066, 1.0626275, 7.6587523, 4.9382973, 9.5788115
};

Stats expect =
{
    .sumsq = 425.1641,
    .sum = 55.84602,
    .min = 0.333,
    .max = 9.678,
    .count = 10
};

double expect_mean = 5.584602;
double expect_stddev = 3.547868;

#define EQ(X, Y, N) \
    (round((X) * pow(10, (N))) == round((Y) * pow(10, (N))))

char *test_operations()
{
    int i = 0;
    Stats *stats = Stats_create();
    mu_assert(stats != NULL, "Failed to create stats.");

    for (i = 0; i < NUM_SAMPLES; i++)
    {
        Stats_sample(stats, samples[i]);
    }

    Stats_dump(stats);

    mu_assert(EQ(stats->sumsq, expect.sumsq, 3), "sumsq not valid");
    mu_assert(EQ(stats->sum, expect.sum, 3), "sum not valid");
    mu_assert(EQ(stats->min, expect.min, 3), "min not valid");
    mu_assert(EQ(stats->max, expect.max, 3), "max not valid");
    mu_assert(EQ(stats->count, expect.count, 3), "count not valid");
    mu_assert(EQ(Stats_mean(stats), expect_mean, 3), "mean not valid");
    mu_assert(EQ(Stats_stddev(stats), expect_stddev, 3), "stddev not valid");

    return NULL;
}

char *test_recreate()
{
    Stats *stats = Stats_recreate(
        expect.sum, expect.sumsq, expect.count, expect.min, expect.max);

    mu_assert(stats->sum == expect.sum, "sum not equal");
    mu_assert(stats->sumsq == expect.sumsq, "sumsq not equal");
    mu_assert(stats->count == expect.count, "count not equal");
    mu_assert(stats->min == expect.min, "min not equal");
    mu_assert(stats->max == expect.max, "max not equal");
    mu_assert(EQ(Stats_mean(stats), expect_mean, 3), "mean not valid");
    mu_assert(EQ(Stats_stddev(stats), expect_stddev, 3), "stddev not valid");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_operations);
    mu_run_test(test_recreate);

    return NULL;
}

RUN_TESTS(all_tests);
