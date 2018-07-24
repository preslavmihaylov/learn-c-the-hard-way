#include <ss_stats.h>

SS_Stats *ss_stats_create()
{
    SS_Stats *statsRepo = calloc(1, sizeof(SS_Stats));
    check(statsRepo != NULL, "Failed to create SS_Stats");

    statsRepo->data = Hashmap_create(NULL, NULL);
    check(statsRepo->data != NULL, "Failed to create Hashmap");

    return statsRepo;

error:
    return NULL;
}

int ss_stats_add(SS_Stats *statsRepo, bstring key)
{
    Stats *newStats = NULL;
    Stats *oldStats = NULL;

    check(statsRepo != NULL, "ss_stats cannot be null");
    check(statsRepo->data != NULL, "ss_stats->data cannot be NULL");
    check(key != NULL, "key cannot be NULL");

    void *val = Hashmap_get(statsRepo->data, key);
    check(val == NULL, "Key already exists in statsRepo");

    newStats = Stats_create();
    check_mem(newStats);

    oldStats = Hashmap_set(statsRepo->data, key, newStats);
    check(oldStats == newStats, "Unexpected overwrite of value when using ss_stats_add");

    return 0;

error:
    if (newStats) Stats_destroy(newStats);
    if (oldStats) Stats_destroy(oldStats);

    return -1;
}

int ss_stats_mean(SS_Stats *statsRepo, bstring key, double *mean)
{
    check(statsRepo != NULL, "statsRepo cannot be NULL");
    check(key != NULL, "key cannot be NULL");

    Stats *currStats = Hashmap_get(statsRepo->data, key);
    check(currStats != NULL, "key does not exist in statsRepo");
    check(currStats->count > 0, "statsRepo should have at least 1 element for calculating mean");

    *mean = Stats_mean(currStats);

    return 0;

error:
    return -1;
}

Stats *ss_stats_dump(SS_Stats *statsRepo, bstring key)
{
    check(statsRepo != NULL, "statsRepo cannot be NULL");
    check(statsRepo->data != NULL, "statsRepo->data cannot be NULL");
    check(key != NULL, "key cannot be NULL");

    return Hashmap_get(statsRepo->data, key);

error:
    return NULL;
}

int ss_stats_delete(SS_Stats *statsRepo, bstring key)
{
    check(statsRepo != NULL, "statsRepo cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(Hashmap_get(statsRepo->data, key) != NULL, "key does not exist");

    void *data = Hashmap_delete(statsRepo->data, key);
    check(data != NULL, "Hashmap failed to delete data");
    Stats_destroy((Stats *)data);

    return 0;

error:
    return -1;
}

int ss_stats_sample(SS_Stats *statsRepo, bstring key, double sample)
{
    check(statsRepo != NULL, "statsRepo cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(statsRepo->data != NULL, "statsRepo->data cannot be NULL");

    Stats *currStats = Hashmap_get(statsRepo->data, key);
    check(currStats != NULL, "key %s  does not exist", bdata(key));

    Stats_sample(currStats, sample);

    return 0;

error:
    return -1;
}

int ss_stats_set(SS_Stats *statsRepo, bstring key, Stats *stats)
{
    check(statsRepo != NULL, "ss_stats cannot be null");
    check(statsRepo->data != NULL, "ss_stats->data cannot be NULL");
    check(key != NULL, "key cannot be NULL");
    check(stats != NULL, "stats cannot be NULL");

    // ignore error. We create a new key if it is non-existent
    //ss_stats_delete(statsRepo, key);

    Stats *oldRecord = Hashmap_set(statsRepo->data, key, stats);
    check(oldRecord != NULL, "Hashmap_set unexpectedly failed in ss_stats_set");

    if (oldRecord != stats) Stats_destroy(oldRecord);

    return 0;

error:
    return -1;
}

void ss_stats_traverse(SS_Stats *statsRepo, ss_stats_traverse_cb cb)
{
    Hashmap_traverse(statsRepo->data, (Hashmap_traverse_cb)cb);
}

static bool stats_destroy_cb(void *key, void *data)
{
    Stats_destroy((Stats *)data);
    return true;
}

void ss_stats_destroy(SS_Stats *statsRepo)
{
    if (statsRepo)
    {
        Hashmap_traverse(statsRepo->data, stats_destroy_cb);
        if (statsRepo->data) Hashmap_destroy(statsRepo->data);

        free(statsRepo);
    }
}
