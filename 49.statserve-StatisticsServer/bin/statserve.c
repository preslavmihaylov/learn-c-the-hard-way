#include <server.h>
#include <unistd.h>
#include <lcthw/dbg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <lcthw/bstrlib.h>
#include <ss_command.h>
#include <ss_stats.h>

void handle_sigchild(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int setup_sig()
{
    struct sigaction sa = {
        .sa_handler = handle_sigchild,
        .sa_flags = SA_RESTART | SA_NOCLDSTOP
    };

    sigemptyset(&sa.sa_mask);
    int rc = sigaction(SIGCHLD, &sa, 0);
    check(rc == 0, "Failed to setup signal");

    return 0;

error:
    return -1;
}

bool stats_destroy_keys_cb(bstring key, Stats *currStats)
{
    if (key) bdestroy(key);
    return true;
}

int execute_cmd(int client_fd, SS_Stats *stats, SS_Command *cmd)
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
        default:
        {
            check(false, "Invalid command detected");
        }
    }

    printf("%s", bdata(resultStr));
    write(client_fd, bdata(resultStr), blength(resultStr)+1);
    bdestroy(resultStr);

    return 0;

error:
    if (resultStr) bdestroy(resultStr);

    return -1;
}

int process_cmd(int client_fd, SS_Stats *stats, char *cmdStr)
{
    bstring errorMsg = NULL;
    bstring line = NULL;
    SS_Command *cmd = NULL;
    int rc = 0;

    line = bfromcstr(cmdStr);
    rc = btrimws(line);
    check(rc == 0, "Failed to trim %s", cmdStr);

    cmd = ss_command_parse(line);
    if (cmd == NULL)
    {
        errorMsg = bformat("Invalid command format. Closing connection\n");
        rc = -1;

        check(false, "Invalid command format. Closing connection");
    }

    rc = execute_cmd(client_fd, stats, cmd);
    if (rc != 0)
    {
        errorMsg = bformat("Error executing cmd: %s. Closing connection\n", bdata(line));
        rc = -1;

        check(false, "Error executing cmd: %s", bdata(line));
    }

error: // fallthrough
    if (errorMsg)
    {
        write(client_fd, bdata(errorMsg), blength(errorMsg)+1);
        bdestroy(errorMsg);
    }

    if (line) bdestroy(line);
    if (cmd) ss_command_destroy(cmd);

    return rc;
}

void child_handler(int client_fd)
{
    char str[100];
    int rc = 0;

    SS_Stats *stats = ss_stats_create();
    check(stats != NULL, "Failed to create stats");

    while (true)
    {
        bzero(str, 100);
        rc = read(client_fd, str, 100);
        if (rc <= 0) break;

        rc = process_cmd(client_fd, stats, str);
        check(rc == 0, "Error occured while processing command: %s", str);
    }

error: // fallthrough
    if (stats)
    {
        ss_stats_traverse(stats, stats_destroy_keys_cb);
        ss_stats_destroy(stats);
    }

    printf("connection with client closed\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    int rc;
    int server_fd;

    check(argc == 2, "Usage: %s <port>", argv[0]);

    rc = setup_sig();
    check(rc == 0, "failed to setup signal");

    server_fd = run_server(atoi(argv[1]));
    while (true)
    {
        // get client comms fd from server
        int client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);
        printf("connection accepted from client\n");

        int child_rc = fork();
        if (child_rc == 0)
        {
            // child process here
            child_handler(client_fd);
        }
        else
        {
            // server process here
            close(client_fd);
        }
    }

    return 0;

error:
    return -1;
}

