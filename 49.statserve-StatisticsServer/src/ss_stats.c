#include <ss_stats.h>

SS_Stats *ss_stats_create()
{
    SS_Stats *stats = calloc(1, sizeof(SS_Stats));
    check(stats != NULL, "Failed to create SS_Stats");

    stats->data = Hashmap_create(NULL, NULL);
    check(stats->data != NULL, "Failed to create Hashmap");

    return stats;

error:
    return NULL;
}

int ss_stats_add(SS_Stats *stats, bstring name)
{
    check(stats != NULL, "ss_stats cannot be null");
    check(stats->data != NULL, "ss_stats->data cannot be NULL");
    check(name != NULL, "Name cannot be NULL");

    Stats *newStats = Stats_create();
    check_mem(newStats);

    Hashmap_set(stats->data, name, newStats);

    return 0;

error:
    return -1;
}

double ss_stats_mean(SS_Stats *stats, bstring name)
{
    return 0;
}

Stats *ss_stats_dump(SS_Stats *stats, bstring name)
{
    return NULL;
}

void ss_stats_delete(SS_Stats *stats, bstring name)
{
}

void ss_stats_sample(SS_Stats *stats, bstring name, double sample)
{
}

void ss_stats_destroy(SS_Stats *stats)
{
}
