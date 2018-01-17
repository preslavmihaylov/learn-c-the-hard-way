#include <stdlib.h>
#include <lcthw/stats.h>

Stats *Stats_recreate(
    double sum, double sumsq, uint32_t count,
    double min, double max)
{
    return NULL;
}

Stats *Stats_create()
{
    return NULL;
}


double Stats_mean(Stats *stats)
{
    return 0;
}

double Stats_stddev(Stats *stats)
{
    return 0;
}


void Stats_sample(Stats *stats, double sample)
{
    return;
}

void Stats_dump(Stats *stats)
{
    return;
}

