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

SS_Command *ss_command_parse(bstring line)
{
    SS_Command *cmd = NULL;
    int rc = 0;
    check(line != NULL, "Line cannot be NULL");

    cmd = ss_command_create();
    cmd->cmdType = SS_CmdType_Create;

    // TODO: Validation for valid cmd
    struct bstrList *tokens = bsplit(line, ' ');
    cmd->parm1 = bstrcpy(tokens->entry[1]);

    rc = bstrListDestroy(tokens);
    check(rc == 0, "bstrListDestroy returned bad exit code");

    return cmd;

error:
    if (cmd) ss_command_destroy(cmd);

    return NULL;
}

void ss_command_destroy(SS_Command *cmd)
{
    if (cmd) free(cmd);
}

