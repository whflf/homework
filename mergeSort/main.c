#include <stdlib.h>

#include "module/errors.h"
#include "module/menuInterface.h"
#include "module/list.h"
#include "module/tests.h"
#include "module/fileUtils.h"

#define INPUT_FILE_NAME "book.txt"

int main(void)
{
    if (!passTests())
    {
        return printErrorMessage(testsFailed, NULL);
    }

    ErrorCode error = ok;

    char* content = NULL;
    size_t fileSize = 0;

    if ((error = readFile(INPUT_FILE_NAME, &content, &fileSize)) != ok)
    {
        return error;
    }

    if (fileSize == 0)
    {
        return printErrorMessage(emptyInputFile, INPUT_FILE_NAME);
    }

    List* phoneBook = NULL;

    if ((error = deserializeBookContent(content, &phoneBook)) != ok)
    {
        deleteList(&phoneBook);
        free(content);
        return error;
    }

    error = programLoop(phoneBook);

    deleteList(&phoneBook);
    free(content);

    return error;
}
