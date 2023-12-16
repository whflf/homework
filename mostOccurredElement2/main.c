#include <stdio.h>
#include <stdlib.h>

#include "include/errors.h"
#include "mostOccurredElement.h"
#include "tests.h"

#define INPUT_FILE_NAME "input.txt"

int main(void)
{
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