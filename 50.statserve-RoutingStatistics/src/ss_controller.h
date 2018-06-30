#ifndef _ss_controller_h
#define _ss_controller_h

#include <ss_stats.h>
#include <ss_command.h>

typedef void (*ss_controller_result_cb)(int client_fd, bstring resultStr);

int ss_controller_execute_cmd(
    int client_fd, SS_Stats *stats, SS_Command *cmd, ss_controller_result_cb resultCallback);

#endif // _ss_controller_h
