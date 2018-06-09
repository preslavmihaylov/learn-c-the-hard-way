#ifndef _ss_stats_h
#define _ss_stats_h

#include <lcthw/hashmap.h>
#include <lcthw/stats.h>
#include <bstrlib.h>

typedef struct SS_Stats {
    Hashmap *data;
} SS_Stats;

SS_Stats *ss_stats_create();

int ss_stats_add(SS_Stats *stats, bstring name);
double ss_stats_mean(SS_Stats *stats, bstring name);
Stats *ss_stats_dump(SS_Stats *stats, bstring name);
void ss_stats_delete(SS_Stats *stats, bstring name);

void ss_stats_sample(SS_Stats *stats, bstring name, double sample);

void ss_stats_destroy(SS_Stats *stats);

#endif // _ss_stats_h
