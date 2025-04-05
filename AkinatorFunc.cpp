#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Errors.h"
#include "colors.h"
#include "MyAssert.h"
#include "DataBase.h"
#include "Input.h"
#include "BinTree.h"
#include "Akinator.h"

ERROR AkinatorRun()
{
    char* str = NULL;
    char* file_name = NULL;
    TreeNode* tree = NULL;
    int ret_val;

    GetInputFile(&file_name, &tree);

    while (true)
    {
        INSTRUCTIONS;

        InputMatch(&ret_val, "Enter [play], [quit], [graph] or [save].", cmd_data, CMD_COUNT);

        switch ((CMD)ret_val)
        {
            case QUIT:
            {
                return NO_ERROR;
            }
            case PLAY:
            {
                AkinatorPlay(&tree);
                break;
            }
            case GRAPH:
            {
                AkinatorGraph(tree);
                break;
            }
            case SAVE:
            {
                AkinatorSave(tree, file_name);
                break;
            }
            case DEF:
            {
                AkinatorDef();
                break;
            }
            default:
                break;
        }
    }

    free(str);
    DeleteTree(&tree);

    YELLOW_TEXT("Come back soon, goodbye!");

    return NO_ERROR;
}

ERROR GetInputFile(char** file_name, TreeNode** tree)
{
    MY_ASSERT(tree,      ADDRESS_ERROR);
    MY_ASSERT(file_name, ADDRESS_ERROR);

    BLUE_TEXT("Enter name of file with base to start.\n");
    InputAnswer(file_name, "Input name of file.");

    FILE* file = NULL;

    _FOPEN(file, *file_name, "ab");
    _FCLOSE(file);

    TreeFromFile(*file_name, tree);

    if (*tree == NULL)
    {
        MAGN_TEXT("File is empty. Tree is empty.\n");
        CreateNode(tree, "Nobody knows who or what is this.");
    }

    return NO_ERROR;
}

ERROR AkinatorPlay(TreeNode** tree)
{
    MY_ASSERT(tree, ADDRESS_ERROR);

    TreeNode* cur = *tree;

    while (true)
    {
        if (cur->left == NULL && cur->right == NULL)
        {
            AkinatorGuess(cur);
            break;
        }

        printf(MAGN "%s\n" RESET_COLOR, cur->data);

        int answer = 0;
        InputMatch(&answer, "Enter [yes] or [no].", state_data, STATE_COUNT);

        switch ((STATE)answer)
        {
            case NO:
            {
                cur = cur->left;
                break;
            }
            case YES:
            {
                cur = cur->right;
                break;
            }
            default:
                break;
        }
    }

    return NO_ERROR;
}
ERROR AkinatorGraph(TreeNode* tree)
{
    TreeDump(tree);

    return NO_ERROR;
}
ERROR AkinatorSave(TreeNode* tree, char* file_name)
{
    if (tree == NULL) YELLOW_TEXT("Tree is empty. Nothing to save.");
    else              TreeToFile(file_name, tree);

    return NO_ERROR;
}
ERROR AkinatorDef()
{
    return NO_ERROR;
}

ERROR AkinatorGuess(TreeNode* cur)
{
    MY_ASSERT(cur, ADDRESS_ERROR);

    printf(CYAN "Is this " RESET_COLOR);
    printf(YELLOW "%s?\n" RESET_COLOR, cur->data);

    int ans = 0;
    InputMatch(&ans, "Enter [yes] or [no].", state_data, STATE_COUNT);

    switch ((STATE)ans)
    {
        case YES:
        {
            YELLOW_TEXT("GG WP EZ GAME I GUESS\n");
            break;
        }
        case NO:
        {
            BLUE_TEXT( "Oh no, I did not guess(((((\n" );
            CYAN_TEXT("But who(what) is this?\n");

            char* who_what = NULL;
            InputAnswer(&who_what, "Enter thing what you thought.");

            printf(CYAN   "What different between " RESET_COLOR);
            printf(YELLOW "%s" RESET_COLOR, who_what);
            printf(CYAN   " and " RESET_COLOR);
            printf(YELLOW "%s" RESET_COLOR, cur->data);
            printf(CYAN   "?\n" RESET_COLOR);

            char* diff = NULL;
            InputAnswer(&diff, "Enter difference between them.");

            CreateNode(&cur->left, cur->data);
            CreateNode(&cur->right, who_what);

            int len = strlen(diff);
            diff = (char*)realloc(diff, len + 2);
            diff[len + 1] = '\0';
            diff[len]     = '?';

            cur->data = diff;
            break;
        }
        default:
            break;
    }
    return NO_ERROR;
}
