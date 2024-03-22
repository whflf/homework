#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module/phoneBook.h"
#include "module/errors.h"
#include "module/tests.h"
#include "module/fileParsing.h"
#include "module/menuInterface.h"

int main(int argc, char* argv[])
{
    for (size_t i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-tests") == 0)
        {
            return passTests() ? 0 : 1;
        }
    }

    if (!passTests())
    {
        return printErrorMessage(testsFailed, NULL, true);
    }

    FILE* file = NULL;

    Book* book = createBook();
    if (book == NULL)
    {
        return printErrorMessage(outOfMemory, "While allocating memory for book in main()", true);
    }

    ErrorCode error = ok;

    fopen_s(&file, BOOK_FILE_NAME, "rb");
    if (file)
    {
        error = readAndDeserializeFile(file, book);
        fclose(file);
        if (error != ok)
        {
            destroyBook(book);
            return error;
        }
    }

    error = programLoop(book);

    destroyBook(book);
    return error;
}
