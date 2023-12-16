﻿#include <stdio.h>
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
