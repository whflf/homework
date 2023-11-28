#include <stdlib.h>

#include "include/tree.h"
#include "include/errors.h"
#include "dialogue.h"
#include "tests.h"

ErrorCode main(void)
{
    if (!passTests())
    {
        printf(errorMessages[testsFailed]);
        return testsFailed;
    }

    Node* dictionary = NULL;
    programLoop(&dictionary);
    deleteTree(&dictionary);

    return ok;
}
