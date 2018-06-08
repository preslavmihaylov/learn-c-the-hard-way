#include <server.h>
#include <unistd.h>
#include <dbg.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    check(argc == 2, "Usage: %s <port>", argv[0]);

    char str[100];
    server_fds serv = run_server(atoi(argv[1]));

    while (true)
    {
        bzero(str, 100);
        read(serv.client_fd, str, 100);

        printf("Echoing back - %s", str);
        write(serv.client_fd, str, strlen(str)+1);
    }

    return 0;

error:
    return -1;
}
