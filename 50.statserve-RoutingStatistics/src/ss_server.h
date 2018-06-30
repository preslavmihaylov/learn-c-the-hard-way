#ifndef _ss_server_h
#define _ss_server_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int ss_server_run(int port);

#endif // _ss_server_h
