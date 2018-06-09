#ifndef _ss_stats_h
#define _ss_stats_h

#include <lcthw/hashmap.h>
#include <lcthw/stats.h>

typedef struct SS_Stats {
    Hashmap data;
} SS_Stats;

SS_Stats *ss_stats_create();

void ss_stats_add(SS_Stats *stats, char *name);
double ss_stats_mean(SS_Stats *stats, char *name);
Stats *ss_stats_dump(SS_Stats *stats, char *name);
void ss_stats_delete(SS_Stats *stats, char *name);

void ss_stats_sample(SS_Stats *stats, char *name, double sample);

void ss_stats_destroy(SS_Stats *stats);

#endif // _ss_stats_h
