#include <stdlib.h>
#include <math.h>
#include <lcthw/dbg.h>
#include <lcthw/stats.h>

Stats *Stats_recreate(
    double sum, double sumsq, uint32_t count,
    double min, double max)
{
    Stats *stats = Stats_create();
    check_mem(stats);

    stats->sum = sum;
    stats->sumsq = sumsq;
    stats->count = count;
    stats->min = min;
    stats->max = max;

    return stats;

error:
    return NULL;
}

Stats *Stats_create()
{
    Stats *stats = calloc(1, sizeof(Stats));
    check_mem(stats);

    return stats;

error:
    return NULL;
}


double Stats_mean(Stats *stats)
{
    check(stats != NULL, "Stats cannot be NULL");

    return (stats->sum / stats->count);

error:
    return 0.f;
}

double Stats_stddev(Stats *stats)
{
    check(stats != NULL, "Stats cannot be NULL");

    return sqrt((stats->sumsq - (stats->sum * Stats_mean(stats))) / (stats->count - 1));

error:
    return 0.f;
}


void Stats_sample(Stats *stats, double sample)
{
    check(stats != NULL, "Stats cannot be NULL");

    stats->sum += sample;
    stats->sumsq += sample * sample;

    if (stats->count == 0)
    {
        stats->min = stats->max = sample;
    }
    else
    {
        if (stats->min > sample)
        {
            stats->min = sample;
        }

        if (stats->max < sample)
        {
            stats->max = sample;
        }
    }

    stats->count++;

error: // fallthrough
    return;
}

void Stats_dump(Stats *stats)
{
    fprintf(stderr,
        "sum: %f, sumsq: %f, count: %u, "
        "min: %f, max: %f, mean: %f, stddev: %f\n",
        stats->sum, stats->sumsq, stats->count, stats->min,
        stats->max, Stats_mean(stats), Stats_stddev(stats));
}

