#ifndef _STACK_H_
#define _STACK_H_

#include "Errors.h"

#define DEFAULT_STACK_CAPACITY 10

struct DefNode
{
    char* str = NULL;
    char  way = 0;
};

typedef DefNode* StackType;

enum STACK_CHANGE
{
    UP = 1,
    DOWN = 0
};

struct Stack
{
    StackType * data = NULL;

    size_t size = 0;
    size_t capacity = 0;
};

ERROR StackCtor(Stack ** stk, size_t capacity);
ERROR StackPop(Stack * stk, StackType * var);
ERROR StackChange(Stack * stk, STACK_CHANGE condition);
ERROR StackPush(Stack * stk, StackType value);
ERROR StackDump(Stack * stk);
ERROR StackDtor(Stack ** stk);

#endif //_STACK_H_
