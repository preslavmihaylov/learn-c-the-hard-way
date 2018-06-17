#ifndef _ss_protocol_h
#define _ss_protocol_h

#include <lcthw/bstrlib.h>

typedef enum {
    SS_CmdType_None,
    SS_CmdType_Create,
    SS_CmdType_Mean,
    SS_CmdType_Sample,
    SS_CmdType_Dump,
    SS_CmdType_Count
} SS_CmdType;

typedef struct SS_Command {
    SS_CmdType cmdType;
    bstring parm1;
    bstring parm2;
} SS_Command;

SS_Command *ss_command_create();
SS_Command *ss_command_parse(bstring line);
void ss_command_destroy(SS_Command *cmd);

#endif // _ss_protocol_h
