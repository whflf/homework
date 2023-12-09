#include <stdlib.h>
#include <stdio.h>

#include "modules/errors.h"
#include "modules/tree.h"
#include "modules/fileParsing.h"
#include "modules/tests.h"

#define INPUT_FILE_NAME "expression.txt"

ErrorCode main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed);
    }

    ErrorCode error = ok;
    Node* parseTree = fileToTree(INPUT_FILE_NAME, &error);
    if (error != ok)
    {
        return printErrorMessage(error);
    }

    printTree(parseTree, stdout);
    printf("= %d\n", getResult(parseTree));
    deleteTree(&parseTree);

    return ok;
}

