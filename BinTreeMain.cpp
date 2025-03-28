#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinTree.h"

int main()
{
    printf(CYAN "Hello! Welcome to GuessInator 2000.\n"
                "Enter:\n"
                "[play]  to play with ready-made database\n"
                "[quit]  to quit\n"
                "[graph] to create graph of database tree\n"
                "[save]  to save new data in database\n"
                "[new]   to start new database\n" RESET_COLOR);


    //char* answer =

    //InputCheck();

    char str1[10] = "Base.txt";

    TreeNode* tree = NULL;

    TreeFromFile(str1, &tree);

    TreeDump(tree);

    DeleteTree(&tree);

    return NO_ERROR;
}
