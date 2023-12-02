#include <stdio.h>
#include <stdlib.h>

#include "module/phoneBook.h"
#include "module/errors.h"
#include "module/tests.h"
#include "module/fileParsing.h"
#include "module/menuInterface.h"

int main(void)
{
    if (!passTests())
    {
        printf("Tests failed. Exiting.\n");
        return testsFailed;
    }

    FILE* file = NULL;

    Book* book = createBook();
    if (book == NULL)
    {
        printf("Failed to allocate memory. Exiting.\n");
        return outOfMemory;
    }

    fopen_s(&file, BOOK_FILE_NAME, "rb");
    if (file)
    {
        const ErrorCode error = readAndSerializeFile(file, book);
        fclose(file);
        if (error)
        {
            destroyBook(book);
            return error;
        }
    }

    programLoop(book);

    destroyBook(book);
    return ok;
}
