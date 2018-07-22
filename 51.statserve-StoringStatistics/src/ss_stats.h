#ifndef _ss_stats_h
#define _ss_stats_h

#include <lcthw/hashmap.h>
#include <lcthw/stats.h>
#include <lcthw/bstrlib.h>

typedef struct SS_Stats {
    Hashmap *data;
} SS_Stats;

SS_Stats *ss_stats_create();

int ss_stats_add(SS_Stats *statsRepo, bstring key);
int ss_stats_mean(SS_Stats *statsRepo, bstring key, double *mean);

Stats *ss_stats_dump(SS_Stats *statsRepo, bstring key);
int ss_stats_delete(SS_Stats *statsRepo, bstring key);

int ss_stats_sample(SS_Stats *statsRepo, bstring key, double sample);
int ss_stats_set(SS_Stats *statsRepo, bstring key, Stats *stats);

typedef bool (*ss_stats_traverse_cb) (bstring key, Stats *currStats);
void ss_stats_traverse(SS_Stats *statsRepo, ss_stats_traverse_cb cb);

void ss_stats_destroy(SS_Stats *statsRepo);

#endif // _ss_stats_h
