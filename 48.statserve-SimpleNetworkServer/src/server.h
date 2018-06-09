#ifndef _server_h
#define _server_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int run_server(int port);

#endif // _server_h
