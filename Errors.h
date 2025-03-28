#ifndef _ERRORS_H_
#define _ERRORS_H_

enum ERROR
{
    NO_ERROR = 0,

    OPEN_FILE_ERROR   = 1,
    CLOSE_FILE_ERROR  = 2,
    ADDRESS_ERROR     = 3,
    NO_NODE_IN_LIST   = 4,
    DELETE_NODE_ERROR = 5,
    CALLOC_ERROR      = 6,
    FILE_READ_ERROR   = 7,
    POP_ERROR         = 8,
    CHANGE_ERROR      = 9,
    STK_ADDRESS_ERROR = 10
};

#endif //_ERRORS_H_
