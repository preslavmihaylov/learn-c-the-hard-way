#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define STDIN_FD 0

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

int read_some(RingBuffer *inputRB, int fd, bool isSocket)
{
    int rc = 0;
    char input[RingBuffer_available_space(inputRB)];
   
    // TODO: Socket read
    rc = read(fd, input, RingBuffer_available_space(inputRB));
    check(rc >= 0, "Couldn't read anything"); 
    RingBuffer_write(inputRB, input, rc);

    //input[RingBuffer_available_data(inputRB)] = 0;
    //rc = RingBuffer_read(inputRB, input, RingBuffer_available_data(inputRB));
    //check(rc == 0, "RingBuffer_read failed\n");
    //printf("%s", input);

    return rc;

error: 
    return -1;
}

int main(int argc, char *argv[])
{
    fd_set allreads;
    fd_set readmask;
    int rc = 0;

    check(argc == 3, "USAGE: netclient <host> <port>");

    int conn = client_connect(argv[1], argv[2]);

    RingBuffer *stdinRB = RingBuffer_create(1024 * 10);

    FD_ZERO(&allreads);
    FD_SET(conn, &allreads);
    FD_SET(STDIN_FD, &allreads);

    while (true)
    {
        readmask = allreads;

        //rc = select(socket + 1, &readmask, NULL, NULL, NULL);
        check(rc >= 0, "select failed");

        if (FD_ISSET(STDIN_FD, &readmask))
        {
            rc = read_some(stdinRB, 0, false);
            check_debug(rc != -1, "Failed to read from stdin");
        }
    }

    return 0;

error:
    return -1;
}
