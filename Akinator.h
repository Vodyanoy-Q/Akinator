#ifndef _AKINATOR_H_
#define _AKINATOR_H_

#include "Errors.h"
#include "colors.h"
#include "BinTree.h"

#define INSTRUCTIONS printf(CYAN "Enter:\n"                                                  \
                                 "[play]  to play with ready-made database\n"                \
                                 "[quit]  to quit\n"                                         \
                                 "[graph] to create graph of database tree\n"                \
                                 "[save]  to save new data in database\n"                    \
                                 "[def]   to start new database and play\n" RESET_COLOR);    \


ERROR AkinatorRun();
ERROR AkinatorPlay(TreeNode** tree);
ERROR AkinatorGraph(TreeNode* tree);
ERROR AkinatorSave(TreeNode* tree, char* file_name);
ERROR AkinatorDef();
ERROR AkinatorGuess(TreeNode* cur);
ERROR GetInputFile(char** file_name, TreeNode** tree);

#endif //_AKINATOR_H_
