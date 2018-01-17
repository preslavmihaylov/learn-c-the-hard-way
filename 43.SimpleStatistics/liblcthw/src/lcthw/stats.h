#ifndef LCTHW_STATS_H
#define LCTHW_STATS_H

#include <stdint.h>

typedef struct Stats
{
    double sum;
    double sumsq;
    uint32_t count;
    double min;
    double max;
} Stats;

Stats *Stats_recreate(
    double sum, double sumsq, uint32_t count,
    double min, double max);
Stats *Stats_create();

double Stats_mean(Stats *stats);
double Stats_stddev(Stats *stats);

void Stats_sample(Stats *stats, double sample);
void Stats_dump(Stats *stats);

#endif // LCTHW_STATS_H
