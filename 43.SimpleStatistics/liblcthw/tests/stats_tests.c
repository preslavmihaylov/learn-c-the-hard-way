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
    return NULL;
}

char *test_recreate()
{
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
