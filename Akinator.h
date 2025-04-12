#ifndef _AKINATOR_H_
#define _AKINATOR_H_

#include "Errors.h"
#include "colors.h"
#include "BinTree.h"
#include "Stack.h"

enum FoundCondition
{
    NOT_FOUND = 0,
    FOUND     = 1
};

enum WAY
{
    LEFT  = 0,
    RIGHT = 1
};

ERROR AkinatorRun();
ERROR AkinatorPlay(TreeNode** tree);
ERROR AkinatorGraph(TreeNode* tree);
ERROR AkinatorSave(TreeNode* tree, char* file_name);
ERROR AkinatorDef(TreeNode* tree);
ERROR AkinatorGuess(TreeNode* cur);
ERROR GetInputFile(char** file_name, TreeNode** tree);
ERROR AkinatorFind(TreeNode* cur, Stack* stk, const char* word, FoundCondition* ret_val);
ERROR AkinatorDifference(TreeNode* tree);
ERROR Instructions();
ERROR PrintDifference(Stack* stk);
ERROR CreateDefNode(DefNode** ret_ptr, char way, char* str);

#endif //_AKINATOR_H_
