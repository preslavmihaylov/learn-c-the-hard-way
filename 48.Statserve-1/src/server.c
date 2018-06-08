#include <server.h>

server_fds run_server(int port)
{
    int server_fd;
    int client_fd;
    struct sockaddr_in servaddr;

    // create socket for AF_INET (IPv4 comms)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // memset struct to all zero bytes
    bzero(&servaddr, sizeof(servaddr));

    // set server properties (IPv4 server, accept all IPs, port)
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // bind server with properties to server fd
    bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // listen on specified server fd and accept at maximum 10 holding connections
    listen(server_fd, 10);

    printf("Server listening on port %d\n", port);

    // get client comms fd from server
    client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);

    server_fds serv = { .server_fd = server_fd, .client_fd = client_fd };
    return serv;
}
