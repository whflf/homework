#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phoneBook.h"
#include "errors.h"
#include "tests.h"
#include "fileParsing.h"
#include "menuInterface.h"

int main(void)
{
    if (!passTests())
    {
        printf("Tests failed. Exiting.\n");
        return testsFailed;
    }

    FILE* file = NULL;

    Book* const book = createBook();
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
