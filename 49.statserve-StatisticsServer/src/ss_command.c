#include <stdlib.h>
#include <ss_command.h>
#include <lcthw/dbg.h>

SS_Command *ss_command_create()
{
    SS_Command *cmd = calloc(1, sizeof(SS_Command));
    check_mem(cmd);

    return cmd;

error:
    return NULL;
}

int parse_cmd(SS_Command *cmd, bstring line)
{
    return 0;
}

void ss_command_destroy()
{

}

