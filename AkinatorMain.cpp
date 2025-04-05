#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Akinator.h"
#include "Errors.h"
#include "colors.h"

int main()
{
    printf(CYAN "Hello! Welcome to GuessInator 2000.\n" RESET_COLOR);

    AkinatorRun();

    return NO_ERROR;
}
