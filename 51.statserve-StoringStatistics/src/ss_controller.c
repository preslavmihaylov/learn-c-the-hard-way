#include <ss_controller.h>
#include <lcthw/bstrlib.h>

typedef int (*ss_controller_traverse_cb) (SS_Stats *stats, bstring originalKey, bstring currentKey, double value);

static int ss_controller_create_key(SS_Stats *stats, bstring key);
static int ss_controller_sample_key(SS_Stats *stats, bstring key, double value);
static int ss_controller_create_cb(SS_Stats *stats, bstring originalKey, bstring currentKey, double value);
static int ss_controller_sample_cb(SS_Stats *stats, bstring originalKey, bstring currentKey, double value);
static int ss_controller_traverse_url(
    SS_Stats *stats, bstring url, double value, ss_controller_traverse_cb traverseCb);

static struct tagbstring ROOT_KEY = bsStatic("/");

int ss_controller_execute_cmd(
    int client_fd, SS_Stats *stats, SS_Command *cmd, ss_controller_result_cb resultCallback)
{
    bstring resultStr = NULL;
    int rc = 0;

    switch (cmd->cmdType)
    {
        case SS_CmdType_Create:
        {
            check(cmd->paramsCnt == 1, "Invalid params cnt for create cmd");

            // remember to destroy key
            rc = ss_controller_create_key(stats, cmd->parm1);
            check(rc == 0, "Failed to add %s key to statistics", bdata(cmd->parm1));

            resultStr = bformat("Key %s successfullly added to statistics\n", cmd->parm1);
            break;
        }
        case SS_CmdType_Mean:
        {
            check(cmd->paramsCnt == 1, "Invalid params cnt for mean cmd");

            double result = 0;
            rc = ss_stats_mean(stats, cmd->parm1, &result);
            check(rc == 0, "Failed to get mean for key %s", bdata(cmd->parm1));

            resultStr = bformat("The mean for key %s is %.2f\n", bdata(cmd->parm1), result);
            break;
        }
        case SS_CmdType_Dump:
        {
            check(cmd->paramsCnt == 1, "Invalid params cnt for dump cmd");

            Stats *currStats = ss_stats_dump(stats, cmd->parm1);
            check(currStats != NULL, "Failed to dump stats for key %s", bdata(cmd->parm1));

            resultStr = bformat("Dumped stats: "
                "sum=%.2f, sumsq=%.2f, count=%u, "
                "min=%.2f, max=%.2f, mean=%.2f, stddev=%.2f\n",
                currStats->sum, currStats->sumsq, currStats->count,
                currStats->min, currStats->max,
                Stats_mean(currStats), Stats_stddev(currStats));

            break;
        }
        case SS_CmdType_Sample:
        {
            check(cmd->paramsCnt == 2, "Invalid params cnt for sample cmd");

            char *parm2 = bdata(cmd->parm2);
            //rc = ss_stats_sample(stats, cmd->parm1, atof(parm2));
            rc = ss_controller_sample_key(stats, cmd->parm1, atof(parm2));
            check(rc == 0, "Failed to sample %s for key %s", bdata(cmd->parm2), bdata(cmd->parm1));

            resultStr = bformat("Successfully sampled %s for key %s\n", bdata(cmd->parm2), bdata(cmd->parm1));
            break;
        }
        case SS_CmdType_Exit:
        {
            check(cmd->paramsCnt == 0, "Invalid params cnt for exit cmd");

            resultStr = bformat("Closing connection by request from client.\n");
            resultCallback(client_fd, resultStr);

            exit(0);
        }
        default:
        {
            check(false, "Invalid command detected");
        }
    }

    resultCallback(client_fd, resultStr);
    if (resultStr) bdestroy(resultStr);

    return 0;

error:
    if (resultStr) bdestroy(resultStr);

    return -1;
}

static int ss_controller_create_key(SS_Stats *stats, bstring key)
{
    return ss_controller_traverse_url(stats, key, 0, ss_controller_create_cb);
}

static int ss_controller_sample_key(SS_Stats *stats, bstring key, double value)
{
    return ss_controller_traverse_url(stats, key, value, ss_controller_sample_cb);
}

static int ss_controller_create_cb(SS_Stats *stats, bstring originalKey, bstring currentKey, double value)
{
    bstring keyToAdd = NULL;
    int rc = 0;

    log_info("attempting to add key %s to stats", bdata(currentKey));
    if (biseq(originalKey, currentKey))
    {
        keyToAdd = bstrcpy(currentKey);
        rc = ss_stats_add(stats, keyToAdd);
        check(rc == 0, "Failed to add key %s to stats", bdata(keyToAdd));
    }
    else
    {
        keyToAdd = bstrcpy(currentKey);
        rc = ss_stats_add(stats, keyToAdd);
        if (rc != 0) bdestroy(keyToAdd);
    }

    return 0;

error:
    if (keyToAdd) bdestroy(keyToAdd);

    return -1;
}

static int ss_controller_sample_cb(SS_Stats *stats, bstring originalKey, bstring currentKey, double value)
{
    int rc = ss_stats_sample(stats, currentKey, value);
    check(rc == 0, "ss_stats_sample failed for key %s", bdata(currentKey));

    return 0;

error:
    return -1;
}

static int ss_controller_traverse_url(
    SS_Stats *stats, bstring url, double value, ss_controller_traverse_cb traverseCb)
{
    int rc = 0;
    bstring currentPath = NULL;
    struct bstrList *tokens = bsplit(url, '/');

    currentPath = bfromcstr("");

    rc = traverseCb(stats, url, &ROOT_KEY, value);
    check(rc == 0, "ss_controller_traverse_cb failed for %s", bdata(&ROOT_KEY));

    // skip empty token at start
    for (int i = 1; i < tokens->qty - 1; i++)
    {
        if (blength(tokens->entry[i]) == 0) continue;

        rc = bconcat(currentPath, &ROOT_KEY);
        check(rc == 0, "bconcat for %s and %s failed", bdata(currentPath), bdata(&ROOT_KEY));

        rc = bconcat(currentPath, tokens->entry[i]);
        check(rc == 0, "bconcat for %s and %s failed", bdata(currentPath), bdata(tokens->entry[i]));

        rc = traverseCb(stats, url, currentPath, value);
        check(rc == 0, "ss_controller_traverse_cb failed for %s", bdata(currentPath));
    }

    rc = bconcat(currentPath, &ROOT_KEY);
    check(rc == 0, "bconcat for %s and %s failed", bdata(currentPath), bdata(&ROOT_KEY));

    rc = bconcat(currentPath, tokens->entry[tokens->qty - 1]);
    check(rc == 0,
        "bconcat for %s and %s failed", bdata(currentPath), bdata(tokens->entry[tokens->qty - 1]));

    rc = traverseCb(stats, url, currentPath, value);
    check(rc == 0, "ss_controller_traverse_cb failed for key %s", bdata(currentPath));

    bstrListDestroy(tokens);
    bdestroy(currentPath);

    return 0;

error:
    if (tokens) bstrListDestroy(tokens);
    if (currentPath) bdestroy(currentPath);

    return -1;
}
