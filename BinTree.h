#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "Errors.h"
#include "colors.h"

struct TreeNode
{
    char* data = 0;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
};


ERROR TreeObhod(TreeNode* node, FILE* file);
ERROR CreateNode(TreeNode** root, const char* elem);
ERROR InsertNode(TreeNode** root, const char* elem);
ERROR TreeDump(TreeNode* root);
ERROR GetStrCount(char* buff, int* str_count);
ERROR GetFileSymbolsCount(FILE* file, size_t* symb_count);
ERROR DeleteTree(TreeNode** node);
ERROR TreeToFile(const char* file_name, TreeNode* node);//
ERROR FprintTree(TreeNode* node, FILE* file, int tab);
ERROR RecTreeFromFile(char* buff, int* pos, int tab, TreeNode** node);
ERROR TreeFromFile(const char* file_name, TreeNode** node);
ERROR GetSpaceCount(char* buff, int pos, int* space_count);
ERROR TabPrint(int tab, FILE* file);


#endif //_BIN_TREE_H_
