#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinTree.h"

int main()
{
    printf(CYAN "Hello! Welcome to GuessInator 2000.\n" RESET_COLOR);
    INSTRUCTIONS;

    AkinatorRun();

    TreeNode* tree = NULL;

    printf("mow\n");

    TreeFromFile("Base.txt", &tree);

    TreeDump(tree);

    DeleteTree(&tree);

    return NO_ERROR;
}
