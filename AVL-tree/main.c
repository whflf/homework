#include <stdlib.h>
#include <string.h>

#include "modules/tree.h"
#include "modules/errors.h"
#include "modules/dialogue.h"
#include "modules/tests.h"

#define CONSOLE_TESTS_ARGUMENT "-tests"

ErrorCode main(int argc, char* argv[])
{
    for (size_t i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], CONSOLE_TESTS_ARGUMENT) == 0)
        {
            return passTests() ? 0 : 1;
        }
    }


    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    Node* dictionary = NULL;

    const ErrorCode error = programLoop(&dictionary);

    deleteTree(&dictionary);
    return printErrorMessage(error);
}
