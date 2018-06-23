#include <server.h>
#include <unistd.h>
#include <lcthw/dbg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <lcthw/bstrlib.h>
#include <ss_command.h>

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

void child_handler(int client_fd)
{
    char str[100];
    bstring line;
    SS_Command *cmd;
    int rc = 0;

    while (true)
    {
        bzero(str, 100);
        rc = read(client_fd, str, 100);
        if (rc <= 0) break;

        line = bfromcstr(str);
        cmd = ss_command_parse(line);
        if (cmd == NULL)
        {
            char *errorMsg = "Invalid command format. Closing connection";
            write(client_fd, errorMsg, strlen(errorMsg)+1);
            check(false, "Invalid command format. Closing connection");
        }

        printf("Echoing back - %s", str);

        //write(client_fd, str, strlen(str)+1);
        write(client_fd, bdata(line), blength(line)+1);

        bdestroy(line);
        ss_command_destroy(cmd);

        continue;

    error:
        if (line) bdestroy(line);
        if (cmd) ss_command_destroy(cmd);

        break;
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

