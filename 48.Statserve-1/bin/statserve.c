#include <server.h>
#include <unistd.h>
#include <dbg.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char str[100];
    int rc;
    int server_fd;

    check(argc == 2, "Usage: %s <port>", argv[0]);

    server_fd = run_server(atoi(argv[1]));
    while (true)
    {
        // get client comms fd from server
        int client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);
        printf("connection accepted from client\n");

        while (true)
        {
            bzero(str, 100);
            rc = read(client_fd, str, 100);
            if (rc <= 0) break;

            printf("Echoing back - %s", str);
            write(client_fd, str, strlen(str)+1);
        }

        printf("connection with client closed\n");
    }

    return 0;

error:
    return -1;
}
