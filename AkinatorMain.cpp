#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Akinator.h"
#include "Errors.h"
#include "colors.h"

int main()
{
    CYAN_TEXT( "Hello! Welcome to GuessInator 2000.\n");

    AkinatorRun();

    YELLOW_TEXT("Come back soon, goodbye!\n");

    return NO_ERROR;
}
