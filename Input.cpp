#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MyAssert.h"
#include "Errors.h"
#include "colors.h"
#include "Input.h"

ERROR InputAnswer(char** str, const char* error_message)
{
    MY_ASSERT_RET(str,           ADDRESS_ERROR);
    MY_ASSERT_RET(error_message, ADDRESS_ERROR);

    int check = 0;

    while (true)
    {
        check = scanf("%m[^\n]", str);

        if (check != 1)
        {
            if (check == EOF) clearerr(stdin);
            else              getchar();

            printf(RED "%s\n" RESET_COLOR, error_message);
            continue;
        }
        getchar();
        break;
    }

    return NO_ERROR;
}

ERROR InputMatch(int* ret_val, const char* error_message, const char** match_data, const int data_size)
{
    char* str = NULL;
    int check = 0;

    int* num_data = (int*)calloc(data_size, sizeof(int));
    MY_ASSERT_RET(num_data, ADDRESS_ERROR);

    for (int i = 0; i < data_size; i++)
    {
        num_data[i] = i;
    }

    while (true)
    {
        while ((check = scanf("%m[^\n]", &str)) != 1)
        {
            if (check == EOF) clearerr(stdin);
            else              getchar();

            printf(RED "%s\n" RESET_COLOR, error_message);
        }
        getchar();

        int len = strlen(str);

        for (int i = 0; i < data_size; i++)
        {
            if (strncasecmp(str, match_data[i], len) == 0)
            {
                *ret_val = num_data[i];
                free(str);
                return NO_ERROR;
            }
        }

        printf(RED "%s\n" RESET_COLOR, error_message);
        free(str);
    }
    free(num_data);

    return NO_ERROR;
}
