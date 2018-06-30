#include <ss_server.h>
#include <unistd.h>
#include <lcthw/dbg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <lcthw/bstrlib.h>
#include <ss_controller.h>

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

void execute_cmd_callback(int client_fd, bstring resultStr)
{
    printf("%s", bdata(resultStr));
    write(client_fd, bdata(resultStr), blength(resultStr)+1);
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

    rc = ss_controller_execute_cmd(client_fd, stats, cmd, execute_cmd_callback);
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
    exit(-1);
}

int main(int argc, char *argv[])
{
    int rc;
    int server_fd;

    check(argc == 2, "Usage: %s <port>", argv[0]);

    rc = setup_sig();
    check(rc == 0, "failed to setup signal");

    server_fd = ss_server_run(atoi(argv[1]));
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

