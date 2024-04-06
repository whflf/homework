#include <stdlib.h>
#include <string.h>

#include "modules/tree.h"
#include "modules/errors.h"
#include "modules/dialogue.h"
#include "modules/tests.h"

ErrorCode main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "-tests") == 0)
    {
        return passTests() ? 0 : 1;
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
