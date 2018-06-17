#include <stdlib.h>
#include <ss_command.h>
#include <lcthw/dbg.h>
#include <stdbool.h>

SS_Command *ss_command_create()
{
    SS_Command *cmd = calloc(1, sizeof(SS_Command));
    check_mem(cmd);

    return cmd;

error:
    return NULL;
}

SS_CmdType ss_command_getCmdType(struct bstrList *tokens)
{
    char *firstEntry = bdata(tokens->entry[0]);
    if (strcmp(firstEntry, "create") == 0)
    {
        log_info("Create cmd matched");
        check(tokens->qty == 2, "Invalid cmd length for create");

        return SS_CmdType_Create;
    }

error:
    return SS_CmdType_None;
}

SS_Command *ss_command_parse(bstring line)
{
    SS_Command *cmd = NULL;
    int rc = 0;
    check(line != NULL, "Line cannot be NULL");

    struct bstrList *tokens = bsplit(line, ' ');
    SS_CmdType cmdType = ss_command_getCmdType(tokens);
    check(cmdType != SS_CmdType_None, "command format invalid");

    cmd = ss_command_create();
    cmd->cmdType = cmdType;
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
    if (cmd)
    {
        if (cmd->parm1) bdestroy(cmd->parm1);
        if (cmd->parm2) bdestroy(cmd->parm2);

        free(cmd);
    }
}

