#include <stdlib.h>

#include "include/tree.h"
#include "include/errors.h"
#include "dialogue.h"
#include "tests.h"

int main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    Node* dictionary = NULL;
    
    const ErrorCode error = programLoop(&dictionary);
    if (error != ok)
    {
        printErrorMessage(error);
    }

    deleteTree(&dictionary);
    return error;
}
