﻿#include <stdlib.h>

#include "modules/tree.h"
#include "modules/errors.h"
#include "modules/dialogue.h"
#include "modules/tests.h"

int main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    Node* dictionary = NULL;
    
    const ErrorCode error = programLoop(&dictionary);

    deleteTree(&dictionary);
    return printErrorMessage(error);
}
