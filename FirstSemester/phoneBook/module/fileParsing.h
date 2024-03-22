#pragma once

#include <stdio.h>

#include "errors.h"
#include "phoneBook.h"

ErrorCode readFile(FILE* const file, char** const content, size_t* const fileSize);

ErrorCode readAndDeserializeFile(FILE* const file, Book* const book);
