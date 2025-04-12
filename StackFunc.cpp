#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "colors.h"
#include "MyAssert.h"
#include "Errors.h"

ERROR StackCtor(Stack ** stk, size_t capacity)
{
    Stack * stack = (Stack*)calloc(1, sizeof(Stack));
    MY_ASSERT_RET(stk, ADDRESS_ERROR);

    stack->size = 0;
    stack->capacity = capacity;

    stack->data = (StackType*)calloc(stack->capacity, sizeof(StackType));
    MY_ASSERT_RET(stack->data, ADDRESS_ERROR);

    *stk = stack;

    return NO_ERROR;
}

ERROR StackDtor(Stack ** stk)
{
    MY_ASSERT_RET(*stk, STK_ADDRESS_ERROR);

    for (size_t i = 0; i < (*stk)->size; i++)
    {
        (*stk)->data[i]->way = 0;
        (*stk)->data[i]->str = NULL;
        free((*stk)->data[i]);
    }

    (*stk)->size = 0;
    (*stk)->capacity = 0;

    free((*stk)->data);
    (*stk)->data = NULL;

    free(*stk);

    *stk = NULL;

    return NO_ERROR;
}

ERROR StackPush(Stack * stk, StackType value)
{
    MY_ASSERT_RET(stk, STK_ADDRESS_ERROR);

    if (stk->size == stk->capacity)
    {
        ERROR err = StackChange(stk, UP);

        if (err != 0)
        {
            return err;
        }
    }

    stk->data[stk->size] = value;

    stk->size += 1;

    return NO_ERROR;
}

ERROR StackDump(Stack * stk)
{
    MY_ASSERT_RET(stk, STK_ADDRESS_ERROR);

    YELLOW_TEXT("==================================================\n");

    for (size_t i = 0; i < stk->size; i++)
    {
        printf(YELLOW "%5d | %s\n" RESET_COLOR, stk->data[i]->way, stk->data[i]->str);
    }

    YELLOW_TEXT("==================================================\n");

    return NO_ERROR;
}

ERROR StackPop(Stack * stk, StackType * var)
{
    MY_ASSERT_RET(stk, STK_ADDRESS_ERROR);
    MY_ASSERT_RET(var, ADDRESS_ERROR);

    if (stk->size == 0)
    {
        RED_TEXT("ERROR: STACK IS EMPTY.\n");
        return POP_ERROR;
    }
    else
    {
        *var = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;

        stk->size -= 1;

        if (stk->size == 0)
        {
            stk->capacity = 1;

            return StackChange(stk, DOWN);
        }

        else if (stk->size > 0 && stk->capacity / 4 == stk->size)
        {
            return StackChange(stk, DOWN);
        }
    }

    return NO_ERROR;
}

ERROR StackChange(Stack * stk, STACK_CHANGE condition)
{
    MY_ASSERT_RET(stk, STK_ADDRESS_ERROR);

    switch (condition)
    {
        case UP:
        {
            stk->capacity *= 2;

            stk->data = (StackType*)realloc(stk->data, stk->capacity * sizeof(StackType));
            MY_ASSERT_RET(stk->data, ADDRESS_ERROR);

            break;
        }

        case DOWN:
        {
            if (stk->size == 0)
            {
                stk->capacity = 1;
            }
            else
            {
                stk->capacity /= 4;
            }

            stk->data = (StackType*)realloc(stk->data, stk->capacity * sizeof(StackType));
            MY_ASSERT_RET(stk->data, ADDRESS_ERROR);

            break;
        }

        default:
        {
            RED_TEXT("ERROR STACK CHANGE VALUE\n");
            return CHANGE_ERROR;

            break;
        }
    }

    return NO_ERROR;
}
