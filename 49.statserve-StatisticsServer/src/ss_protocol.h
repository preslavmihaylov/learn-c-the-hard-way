#ifndef _ss_protocol_h
#define _ss_protocol_h

#include <lcthw/bstrlib.h>

typedef enum {
    SS_CmdType_Create,
    SS_CmdType_Mean,
    SS_CmdType_Sample,
    SS_CmdType_Dump
} SS_CmdType;

typedef struct SS_Command {
    SS_CmdType cmdType;
    bstring key;
    void *data;
} SS_Command;

SS_Command ss_command_create();

int parse_cmd(SS_Command *cmd, bstring line);

void ss_command_destroy();

#endif // _ss_protocol_h
