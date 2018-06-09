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

int ss_stats_add(SS_Stats *stats, bstring key)
{
    check(stats != NULL, "ss_stats cannot be null");
    check(stats->data != NULL, "ss_stats->data cannot be NULL");
    check(key != NULL, "key cannot be NULL");

    Stats *newStats = Stats_create();
    check_mem(newStats);

    Hashmap_set(stats->data, key, newStats);

    return 0;

error:
    return -1;
}

double ss_stats_mean(SS_Stats *stats, bstring key)
{
    return 1;
}

Stats *ss_stats_dump(SS_Stats *stats, bstring key)
{
    check(stats != NULL, "stats cannot be NULL");
    check(stats->data != NULL, "stats->data cannot be NULL");
    check(key != NULL, "key cannot be NULL");

    return Hashmap_get(stats->data, key);

error:
    return NULL;
}

int ss_stats_delete(SS_Stats *stats, bstring key)
{
    check(stats != NULL, "stats cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(Hashmap_get(stats->data, key) != NULL, "key does not exist");

    void *data = Hashmap_delete(stats->data, key);
    check(data != NULL, "Hashmap failed to delete data");

    return 0;

error:
    return -1;
}

int ss_stats_sample(SS_Stats *stats, bstring key, double sample)
{
    check(stats != NULL, "stats cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(stats->data != NULL, "stats->data cannot be NULL");

    Stats *currStats = Hashmap_get(stats->data, key);
    check(currStats != NULL, "key does not exist");

    Stats_sample(currStats, sample);

    return 0;

error:
    return -1;
}

void ss_stats_destroy(SS_Stats *stats)
{
}
