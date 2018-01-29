#include <lcthw/dbg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

int nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    check(flags >= 0, "Invalid flags on nonblock");

    int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    check(rc == 0, "Can't set nonblock");

    return 0;

error:
    return -1;
}

int client_connect(char *host, char *port)
{
    int rc;
    struct addrinfo *addrInfo = NULL;

    int conn = socket(AF_INET, SOCK_STREAM, 0);
    check(conn > 0, "Failed to create socket");

    rc = getaddrinfo(host, port, NULL, &addrInfo);
    check(rc == 0, "Failed to lookup %s %s", host, port);

    rc = connect(conn, addrInfo->ai_addr, addrInfo->ai_addrlen);
    check(rc == 0, "Failed to open socket with established connection");

    rc = nonblock(conn);
    check(rc == 0, "Failed to set nonblock");

    freeaddrinfo(addrInfo);
    return conn;

error:
    if (addrInfo) freeaddrinfo(addrInfo);
    return -1;
}

int main(int argc, char *argv[])
{
    check(argc == 3, "USAGE: netclient <host> <port>");

    int fd = client_connect(argv[1], argv[2]);
    (void)fd;

    return 0;

error:
    return -1;
}
