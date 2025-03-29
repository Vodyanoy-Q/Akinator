#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "Errors.h"
#include "colors.h"
#include "MyAssert.h"

#define OPEN_PRINT  for (int j = 0; j < tab; j++)        \
                    {                                    \
                        fprintf(file, "    ");           \
                    }                                    \
                    fprintf(file, "(\n");                \
                    tab++                                \

#define CLOSE_PRINT tab--;                               \
                    for (int j = 0; j < tab; j++)        \
                    {                                    \
                        fprintf(file, "    ");           \
                    }                                    \
                    fprintf(file, ")\n");                \

#define NUM_PRINT   for (int j = 0; j < tab; j++)        \
                    {                                    \
                        fprintf(file, "    ");           \
                    }                                    \
                    fprintf(file, "%s\n", node->data);   \

#define INSTRUCTIONS printf(CYAN "Enter:\n"                                                  \
                                 "[play]  to play with ready-made database\n"                \
                                 "[quit]  to quit\n"                                         \
                                 "[graph] to create graph of database tree\n"                \
                                 "[save]  to save new data in database\n"                    \
                                 "[new]   to start new database and play\n" RESET_COLOR);    \

#define ERROR_INPUT RED_TEXT("Error input. Try again by following instructions.\n");         \
                    INSTRUCTIONS;                                                            \

#define INPUT(str, message)     int check = scanf("%m[^\n]", &str);        \
                                                                           \
                                if (check == EOF)                          \
                                {                                          \
                                    clearerr(stdin);                       \
                                    message;                               \
                                    continue;                              \
                                }                                          \
                                if (check != 1)                            \
                                {                                          \
                                    getchar();                             \
                                    message;                               \
                                    continue;                              \
                                }                                          \
                                getchar();                                 \


struct TreeNode
{
    char* data = 0;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
};

ERROR TreeObhod(TreeNode* node, FILE* file);
ERROR CreateNode(TreeNode** root, char* elem);
ERROR InsertNode(TreeNode** root, char* elem);
ERROR TreeDump(TreeNode* root);
ERROR GetStrCount(char* buff, int* str_count);
ERROR GetFileSymbolsCount(FILE* file, size_t* symb_count);
ERROR DeleteTree(TreeNode** node);
ERROR TreeToFile(char* file_name, TreeNode* node);//
ERROR FprintTree(TreeNode* node, FILE* file, int tab);
ERROR RecTreeFromFile(char* buff, int* pos, int tab, TreeNode** node);
ERROR TreeFromFile(const char* file_name, TreeNode** node);
ERROR GetSpaceCount(char* buff, int pos, int* space_count);
ERROR AkinatorRun();
ERROR AkinatorPlay(TreeNode** tree, const char* file_name);
ERROR AkinatorGraph(TreeNode* tree);
ERROR AkinatorSave(TreeNode* tree);
ERROR AkinatorNew();
ERROR AkinatorGuess(TreeNode* cur);

#endif //_BIN_TREE_H_
