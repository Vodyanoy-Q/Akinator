#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#define CMD_COUNT 6
#define STATE_COUNT 2

enum CMD
{
    QUIT  = 0,
    PLAY  = 1,
    GRAPH = 2,
    SAVE  = 3,
    DEF   = 4,
    DIF   = 5
};

enum STATE
{
    NO  = 0,
    YES = 1
};

const char* cmd_data[CMD_COUNT] = {"quit", "play", "graph", "save", "def", "bdif"};
const char* state_data[STATE_COUNT] = {"no", "yes"};

#endif // _DATA_BASE_H_
