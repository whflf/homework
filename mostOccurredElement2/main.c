#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/errors.h"
#include "mostOccurredElement.h"
#include "tests.h"

#define INPUT_FILE_NAME "input.txt"

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "run tests") == 0)
    {
        return passTests();
    }

    if (!passTests())
    {
        printf("Tests failed.\n");
        return testsFailed;
    }

    ErrorCode error;
    int mostOccurredElementValue;

    if ((error = getMostOccurredElementFromFile(INPUT_FILE_NAME, &mostOccurredElementValue)) != ok)
    {
        if (error == emptyArray)
        {
            printf("Got nothing (array size = 0).\n");
        }
        return error;
    }

    printf(
        "Most occurred number in \"%s\" is %d.\n",
        INPUT_FILE_NAME,
        mostOccurredElementValue
    );

    return ok;
}