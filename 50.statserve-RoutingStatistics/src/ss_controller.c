#include <ss_controller.h>
#include <lcthw/bstrlib.h>

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

            rc = ss_stats_add(stats, bstrcpy(cmd->parm1));
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
            rc = ss_stats_sample(stats, cmd->parm1, atof(parm2));
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
