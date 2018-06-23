#include <stdlib.h>
#include <ss_command.h>
#include <lcthw/dbg.h>
#include <stdbool.h>

static SS_Command *ss_command_create();
static bool ss_command_isNumber(bstring str);
static SS_CmdType ss_command_getCmdType(struct bstrList *tokens);

static int cmdParamsCnt[SS_CmdType_Count] =
{
    0, // SS_CmdType_None
    1, // SS_CmdType_Create
    1, // SS_CmdType_Mean
    2, // SS_CmdType_Sample
    1, // SS_CmdType_Dump
    0, // SS_CmdType_Exit
};

static SS_Command *ss_command_create()
{
    SS_Command *cmd = calloc(1, sizeof(SS_Command));
    check_mem(cmd);

    return cmd;

error:
    return NULL;
}

static bool ss_command_isNumber(bstring str)
{
    for (int i = 0; i < blength(str); i++)
    {
        if (!isdigit(bdata(str)[0])) return false;
    }

    return true;
}

static SS_CmdType ss_command_getCmdType(struct bstrList *tokens)
{
    char *firstEntry = bdata(tokens->entry[0]);
    if (strcmp(firstEntry, "create") == 0)
    {
        check(tokens->qty == 1 + cmdParamsCnt[SS_CmdType_Create], "Invalid cmd length for create");
        return SS_CmdType_Create;
    }
    else if (strcmp(firstEntry, "mean") == 0)
    {
        check(tokens->qty == 1 + cmdParamsCnt[SS_CmdType_Mean], "Invalid cmd length for mean");
        return SS_CmdType_Mean;
    }
    else if (strcmp(firstEntry, "dump") == 0)
    {
        check(tokens->qty == 1 + cmdParamsCnt[SS_CmdType_Dump], "Invalid cmd length for dump");
        return SS_CmdType_Dump;
    }
    else if (strcmp(firstEntry, "sample") == 0)
    {
        check(tokens->qty == 1 + cmdParamsCnt[SS_CmdType_Sample], "Invalid cmd length for sample");
        check(ss_command_isNumber(tokens->entry[2]), "Second Param for sample is expected to be numeric");

        return SS_CmdType_Sample;
    }
    else if (strcmp(firstEntry, "exit") == 0)
    {
        check(tokens->qty == 1 + cmdParamsCnt[SS_CmdType_Exit], "Invalid cmd length for exit");

        return SS_CmdType_Exit;
    }

error: // fallthrough
    return SS_CmdType_None;
}

SS_Command *ss_command_parse(bstring line)
{
    SS_Command *cmd = NULL;
    struct bstrList *tokens = NULL;
    int rc = 0;

    check(line != NULL, "Line cannot be NULL");

    tokens = bsplit(line, ' ');

    SS_CmdType cmdType = ss_command_getCmdType(tokens);
    check(cmdType != SS_CmdType_None, "command format invalid");

    cmd = ss_command_create();
    cmd->cmdType = cmdType;
    cmd->paramsCnt = cmdParamsCnt[cmdType];
    if (cmd->paramsCnt >= 1) cmd->parm1 = bstrcpy(tokens->entry[1]);
    if (cmd->paramsCnt >= 2) cmd->parm2 = bstrcpy(tokens->entry[2]);

    rc = bstrListDestroy(tokens);
    check(rc == 0, "bstrListDestroy returned bad exit code");

    return cmd;

error:
    if (cmd) ss_command_destroy(cmd);
    if (tokens) bstrListDestroy(tokens);

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

