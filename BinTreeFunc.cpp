#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "BinTree.h"

ERROR InsertNode(TreeNode** root, char* elem)
{
    MY_ASSERT(root, ADDRESS_ERROR);
    MY_ASSERT(elem, ADDRESS_ERROR);

    if (*root == NULL) CreateNode(root, elem);

    else if (strcmp(elem, (*root)->data) > 0)
    {
        InsertNode(&((*root)->right), elem);
    }
    else
    {
        InsertNode(&((*root)->left), elem);
    }

    return NO_ERROR;
}

ERROR CreateNode(TreeNode** root, char* elem)
{
    MY_ASSERT(root, ADDRESS_ERROR);
    MY_ASSERT(elem, ADDRESS_ERROR);

    TreeNode* new_node = (TreeNode*)calloc(1, sizeof(TreeNode));
    MY_ASSERT(new_node, CALLOC_ERROR);

    new_node->left  = NULL;
    new_node->right = NULL;
    new_node->data = elem;

    if (*root == NULL)
    {
        *root = new_node;

        return NO_ERROR;
    }

    if (strcmp(elem, (*root)->data) > 0) (*root)->right = new_node;
    else                                  (*root)->left  = new_node;


    return NO_ERROR;
}

ERROR TreeDump(TreeNode* root)
{
    if (root == NULL)
    {
        printf("Root is NULL ptr\n");
        return ADDRESS_ERROR;
    }

    FILE* file = NULL;

    _FOPEN(file, "tree.dot", "w");
    fprintf(file, "digraph {\n");

    TreeObhod(root, file);

    fprintf(file, "}\n");

    _FCLOSE(file);

    system("dot tree.dot -T png -o tree.png");

    return NO_ERROR;
}

ERROR TreeObhod(TreeNode* node, FILE* file)
{
    if (node == NULL) return NO_ERROR;

    fprintf(file, "    node%p [shape = \"Mrecord\",  label=\" {ptr = %p | str = %s | {<f0> left = %p | <f1> right = %p}} \""
                  ", style=\"filled\", fillcolor=\"#BEDAFF\"]\n", node, node, node->data, node->left, node->right);

    if (node->left  != NULL)  fprintf(file, "    node%p:<f0> -> node%p\n", node, node->left );
    if (node->right != NULL)  fprintf(file, "    node%p:<f1> -> node%p\n", node, node->right);

    fprintf(file, "\n");

    TreeObhod(node->left, file);
    TreeObhod(node->right, file);

    return NO_ERROR;
}

ERROR GetFileSymbolsCount(FILE* file, size_t* symb_count)
{
    MY_ASSERT(file,       ADDRESS_ERROR);
    MY_ASSERT(symb_count, ADDRESS_ERROR);

    struct stat st;

    if (fstat(fileno(file), &st) == 0)
    {
        *symb_count = st.st_size;
    }

    return NO_ERROR;
}

ERROR GetStrCount(char* buff, int* str_count)
{
    MY_ASSERT(buff,      ADDRESS_ERROR);
    MY_ASSERT(str_count, ADDRESS_ERROR);

    int str_c = 0;

    while (*buff != '\0')
    {
        if (*buff == '\n')
        {
            *buff = '\0';
            str_c++;
        }
        buff++;
    }

    *str_count = str_c;

    return NO_ERROR;
}

ERROR DeleteTree(TreeNode** node)
{
    if ((*node)->left  != NULL) DeleteTree(&(*node)->left);
    if ((*node)->right != NULL) DeleteTree(&(*node)->right);


    free((*node)->data);
    (*node)->data = NULL;

    free((*node));
    *node = NULL;

    return NO_ERROR;
}

ERROR TreeToFile(char* file_name, TreeNode* node)
{
    MY_ASSERT(file_name, ADDRESS_ERROR);

    FILE* file = NULL;

    _FOPEN(file, file_name, "w")

    FprintTree(node, file, 0);

    _FCLOSE(file);

    return NO_ERROR;
}

ERROR FprintTree(TreeNode* node, FILE* file, int tab)
{
    if (node == NULL) return NO_ERROR;

    NUM_PRINT;

    if (node->left != NULL && node->right != NULL)
    {
        OPEN_PRINT;

        if (node->left  != NULL) FprintTree(node->left, file, tab);

        CLOSE_PRINT;
        OPEN_PRINT;

        if (node->right != NULL) FprintTree(node->right, file, tab);

        CLOSE_PRINT;
    }

    return NO_ERROR;
}

ERROR TreeFromFile(const char* file_name, TreeNode** node)
{
    MY_ASSERT(file_name, ADDRESS_ERROR);
    MY_ASSERT(node,      ADDRESS_ERROR);

    FILE* file = NULL;

    _FOPEN(file, file_name, "rb");

    size_t symb_count = 0;

    GetFileSymbolsCount(file, &symb_count);

    char* buff = (char*)calloc(symb_count, sizeof(char));
    MY_ASSERT(buff, CALLOC_ERROR);

    if (fread((void*)buff, sizeof(char), symb_count, file) != symb_count)
    {
        printf("ERROR READ FROM FILE\n");

        return FILE_READ_ERROR;
    }

    _FCLOSE(file);

    int str_count = 0;

    GetStrCount(buff, &str_count); //

    int pos = 0;

    RecTreeFromFile(buff, &pos, 0, node);

    free(buff);

    return NO_ERROR;
}

ERROR RecTreeFromFile(char* buff, int* pos, int tab, TreeNode** node)
{
    *pos += tab * 4;  // tab = 9 = \t
                      // isspace
                      // strchr
    int len = strlen(buff + *pos);

    char* str = strndup(buff + *pos, len + 1);

    CreateNode(node, str);

    *pos += len + 1;

    int space_count = 0;
    GetSpaceCount(buff, *pos, &space_count);

    if (space_count == tab * 4)
    {
        *pos += space_count;
        if (*(buff + *pos) == '(')
        {
            *pos += 2;
            RecTreeFromFile(buff, pos, tab + 1, &(*node)->left);

            *pos += (tab * 4 + 2) * 2;
            RecTreeFromFile(buff, pos, tab + 1, &(*node)->right);
            *pos += tab * 4 + 2;
        }
    }

    return NO_ERROR;
}

ERROR GetSpaceCount(char* buff, int pos, int* space_count)
{
    MY_ASSERT(buff,        ADDRESS_ERROR);
    MY_ASSERT(space_count, ADDRESS_ERROR);

    int i = 0;

    for (; *(buff + i + pos) == ' '; i++);

    *space_count = i;

    return NO_ERROR;
}

ERROR AkinatorRun()
{
    char* str = NULL;
    TreeNode* tree = NULL;

    while (true)
    {
        INPUT(str, ERROR_INPUT);  //strcasecmp   stricmp or _stricmp   // q = quit

        if      (strcmp(str, "quit")  == 0) {free(str); break;}
        else if (strcmp(str, "play")  == 0) AkinatorPlay(&tree, "Base.txt");
        else if (strcmp(str, "graph") == 0) AkinatorGraph(tree);
        else if (strcmp(str, "save")  == 0) AkinatorSave(tree);
        else if (strcmp(str, "new")   == 0) AkinatorNew();
        else    ERROR_INPUT;

        free(str);
    }

    return NO_ERROR;
}

ERROR AkinatorPlay(TreeNode** tree, const char* file_name)
{
    MY_ASSERT(tree, ADDRESS_ERROR);

    if (*tree == NULL)                    //TODO
    {
        TreeFromFile(file_name, tree);
    }

    TreeNode* cur = *tree;
    char* str = NULL;

    while (true)
    {
        if (cur->left == NULL && cur->right == NULL)
        {
            AkinatorGuess(cur);
            //GREEN_TEXT("Wanna play again?\n");

            // int cont = 0;
            // while (true)
            // {
            //     INPUT(str, RED_TEXT("Enter yes or no. Try again.\n"));
            //     if      (strcmp(str, "yes") == 0) cont = 1;
            //     else if (strcmp(str, "no") == 0)  cur = cur->left;
            // }
            break;
        }

        printf(MAGN "%s\n" RESET_COLOR, cur->data);

        INPUT(str, RED_TEXT("Enter yes or no. Try again.\n"));

        if      (strcmp(str, "yes") == 0) cur = cur->right;
        else if (strcmp(str, "no") == 0)  cur = cur->left;
        else    RED_TEXT("Enter yes or no. Try again.\n");
        free(str);
    }

    return NO_ERROR;
}
ERROR AkinatorGraph(TreeNode* tree)
{
    TreeDump(tree);

    return NO_ERROR;
}
ERROR AkinatorSave(TreeNode* tree)
{
    char str[10] = "Base.txt";

    TreeToFile(str, tree);

    return NO_ERROR;
}
ERROR AkinatorNew()
{
    return NO_ERROR;
}

ERROR AkinatorGuess(TreeNode* cur)
{
    MY_ASSERT(cur, ADDRESS_ERROR);

    printf(CYAN "Is this " RESET_COLOR);
    printf(YELLOW "%s?\n" RESET_COLOR, cur->data);

    char* str = NULL;

    while (true)
    {
        INPUT(str, RED_TEXT("Enter yes or no. Try again.\n"));
        if (strcmp(str, "yes") == 0 || strcmp(str, "no") == 0) break;
    }

    if      (strcmp(str, "yes") == 0)
    {
        YELLOW_TEXT("GG WP EZ GAME I GUESS\n");
    }
    else if (strcmp(str, "no") == 0)
    {
        BLUE_TEXT( "Oh no, I did not guess(((((\n" );
        CYAN_TEXT("But who(what) is this?\n");
        while (true)
        {
            INPUT(str, RED_TEXT("Enter thing which you thought.\n"));
            break;
        }
        printf(CYAN   "What different between " RESET_COLOR);
        printf(YELLOW "%s" RESET_COLOR, str);
        printf(CYAN   " and " RESET_COLOR);
        printf(YELLOW "%s" RESET_COLOR, cur->data);
        printf(CYAN   "?\n" RESET_COLOR);

        char* diff = NULL;
        while (true)
        {
            INPUT(diff, RED_TEXT("Enter difference.\n"));
            break;
        }

        CreateNode(&cur->left, cur->data);
        CreateNode(&cur->right, str);

        cur->data = diff;
    }



    return NO_ERROR;
}

