#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct server_fds {
    int server_fd;
    int client_fd;
} server_fds;

server_fds run_server(int port);
