#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#include "modules/tests.h"

#define INPUT_FILE_NAME "input.txt"

int main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    FILE* const file = fopen(INPUT_FILE_NAME, "r");
    if (file == NULL)
    {
        return printErrorMessage(fileError);
    }

    const ErrorCode error = printComments(file, stdout);
    fclose(file);

    return error;
}
