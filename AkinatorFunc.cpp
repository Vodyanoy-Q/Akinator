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
#include "Stack.h"

ERROR AkinatorRun()
{
    char* str = NULL;
    char* file_name = NULL;
    TreeNode* tree = NULL;
    int ret_val;

    GetInputFile(&file_name, &tree);

    while (true)
    {
        Instructions();

        InputMatch(&ret_val, "Enter [play], [quit], [graph] or [save].", cmd_data, CMD_COUNT);

        switch ((CMD)ret_val)
        {
            case QUIT:
            {
                free(str);
                DeleteTree(&tree);
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
                AkinatorDef(tree);
                break;
            }
            case DIF:
            {
                AkinatorDifference(tree);
                break;
            }
            default:
                break;
        }
    }

    return NO_ERROR;
}

ERROR Instructions()
{
    printf(CYAN "Enter:\n"
                "[play]  to play with ready-made database\n"
                "[quit]  to quit\n"
                "[graph] to create graph of database tree\n"
                "[save]  to save new data in database\n"
                "[def]   to get definition of word\n"
                "[bdif]  to get difference between words\n" RESET_COLOR);

    return NO_ERROR;
}

ERROR GetInputFile(char** file_name, TreeNode** tree)
{
    MY_ASSERT_RET(tree,      ADDRESS_ERROR);
    MY_ASSERT_RET(file_name, ADDRESS_ERROR);

    BLUE_TEXT("Enter name of file with base to start.\n");
    InputAnswer(file_name, "Input name of file.");

    FILE* file = NULL;

    MY_FOPEN_RET(file, *file_name, "ab");
    MY_FCLOSE_RET(file);

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
    MY_ASSERT_RET(tree, ADDRESS_ERROR);

    TreeNode* cur = *tree;

    while (true)
    {
        if (cur->left == NULL && cur->right == NULL)
        {
            AkinatorGuess(cur);
            break;
        }

        printf(MAGN "%s?\n" RESET_COLOR, cur->data);

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

ERROR AkinatorDef(TreeNode* tree)
{
    MY_ASSERT_RET(tree, ADDRESS_ERROR);

    Stack* stk = NULL;
    StackCtor(&stk, DEFAULT_STACK_CAPACITY);

    CYAN_TEXT("Enter the word you want to find a definition for.\n");
    char* word = NULL;

    InputAnswer(&word, "Enter the word you want to find a definition for.");

    FoundCondition ret_val = NOT_FOUND;
    AkinatorFind(tree, stk, word, &ret_val);

    if (stk->size == 0)
    {
        printf(BLUE   "There is no data about " RESET_COLOR);
        printf(YELLOW "%s.\n" RESET_COLOR, word);
    }
    else
    {
        printf(BLUE "I found definition of " RESET_COLOR);
        printf(YELLOW "%s.\n" RESET_COLOR, word);

        printf(YELLOW "%s " RESET_COLOR, word);
        printf(BLUE "is " RESET_COLOR);

        PrintDifference(stk);
    }

    StackDtor(&stk);
    free(word);

    printf(BLUE "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" RESET_COLOR);

    return NO_ERROR;
}

ERROR PrintDifference(Stack* stk)
{
    StackType elem = NULL;
    char c = 0;

    do
    {
        if (c == 0) c++;
        else printf(BLUE ", " RESET_COLOR);

        StackPop(stk, &elem);

        if (elem->way == LEFT)
        {
            printf(RED "NOT %s" RESET_COLOR, elem->str);
        }
        else
        {
            printf(GREEN "%s" RESET_COLOR, elem->str);
        }
    }
    while (stk->size != 0);

    printf(BLUE "." RESET_COLOR);

    return NO_ERROR;
}

ERROR AkinatorFind(TreeNode* cur, Stack* stk, const char* word, FoundCondition* ret_val)
{
    if (cur->left == NULL && cur->right == NULL)
    {
        if(strcasecmp(cur->data, word) == 0)
        {
            *ret_val = FOUND;
            return NO_ERROR;
        }
        else return NO_ERROR;
    }

    DefNode* ptr = NULL;

    CreateDefNode(&ptr, LEFT, cur->data);
    AkinatorFind(cur->left, stk, word, ret_val);
    StackPush(stk, ptr);

    if (*ret_val == FOUND) return NO_ERROR;
    StackPop(stk, &ptr);

    CreateDefNode(&ptr, RIGHT, cur->data);
    AkinatorFind(cur->right, stk, word, ret_val);
    StackPush(stk, ptr);

    if (*ret_val == FOUND) return NO_ERROR;
    StackPop(stk, &ptr);

    return NO_ERROR;
}

ERROR CreateDefNode(DefNode** ret_ptr, char way, char* str)
{
    MY_ASSERT_RET(ret_ptr, ADDRESS_ERROR);

    DefNode* node = (DefNode*)calloc(1, sizeof(DefNode));
    MY_ASSERT_RET(ret_ptr, CALLOC_ERROR);

    node->str = str;
    node->way = way;

    *ret_ptr = node;

    return NO_ERROR;
}

ERROR AkinatorDifference(TreeNode* tree)
{
    MY_ASSERT_RET(tree, ADDRESS_ERROR);

    char* word1 = NULL;
    CYAN_TEXT("Enter the first word to get difference.\n");
    InputAnswer(&word1, "Enter the word you want to find a definition for.");

    Stack* stk1 = NULL;
    StackCtor(&stk1, DEFAULT_STACK_CAPACITY);

    FoundCondition ret_val = NOT_FOUND;
    AkinatorFind(tree, stk1, word1, &ret_val);

    if (ret_val == NOT_FOUND)
    {
        printf(RED "There is no word %s%s%s in database." RESET_COLOR, YELLOW, word1, RESET_COLOR);
        printf(BLUE "Try add word in database and try later." RESET_COLOR);

        free(word1);
        StackDtor(&stk1);

        return NO_ERROR;
    }

    char* word2 = NULL;
    CYAN_TEXT("Enter the first word to get difference.\n");
    InputAnswer(&word2, "Enter the word you want to find a definition for.");

    Stack* stk2 = NULL;
    StackCtor(&stk2, DEFAULT_STACK_CAPACITY);

    ret_val = NOT_FOUND;
    AkinatorFind(tree, stk2, word2, &ret_val);

    if (ret_val == NOT_FOUND)
    {
        printf(RED "There is no word %s%s%s in database." RESET_COLOR, YELLOW, word2, RESET_COLOR);
        printf(BLUE "Try add word in database and try later." RESET_COLOR);

        free(word1);
        free(word2);
        StackDtor(&stk1);
        StackDtor(&stk2);

        return NO_ERROR;
    }

    printf(CYAN "Deffinitions of words were found. Start to get difference...\n" RESET_COLOR);

    StackType way1 = 0;
    StackType way2 = 0;
    char c = 0;

    printf(MAGN "They\'re similar in that they\'re " RESET_COLOR);

    do
    {
        StackPop(stk1, &way1);
        StackPop(stk2, &way2);

        if (way1->way == way2->way && way1->str == way2->str)
        {
            if (c == 0)
            {
                c++;
                printf(MAGN "in that they\'re " RESET_COLOR);
            }
            else printf(BLUE ", " RESET_COLOR);

            if (way1->way == LEFT) printf(RED "NOT %s" RESET_COLOR, way1->str);
            else              printf(GREEN "%s" RESET_COLOR, way1->str);
        }
        else
        {
            if (c == 0) printf(RED "IN NOTHING" RESET_COLOR);
            break;
        }
    }
    while (stk1->size != 0 && stk2->size != 0);

    printf(BLUE ".\n" RESET_COLOR);

    printf(MAGN "And they are different, because " RESET_COLOR);

    printf(YELLOW "%s " RESET_COLOR, word1);
    printf(BLUE "is " RESET_COLOR);
    PrintDifference(stk1);

    printf(BLUE "\nAnd " RESET_COLOR);
    printf(YELLOW "%s " RESET_COLOR, word2);
    printf(BLUE "is " RESET_COLOR);
    PrintDifference(stk2);

    StackDtor(&stk1);
    StackDtor(&stk2);
    free(word1);
    free(word2);

    printf(BLUE "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" RESET_COLOR);

    return NO_ERROR;
}

ERROR AkinatorGuess(TreeNode* cur)
{
    MY_ASSERT_RET(cur, ADDRESS_ERROR);

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

            cur->data = diff;

            BLUE_TEXT("Thank you for this information. I add it into database.\n");
            BLUE_TEXT("==========================================================\n");
            break;
        }
        default:
            break;
    }
    return NO_ERROR;
}
