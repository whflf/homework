#pragma once

#include <stdio.h>

#include "errors.h"
#include "phoneBook.h"

ErrorCode readFile(FILE* file, char** content, long* const fileSize);

ErrorCode readAndSerializeFile(FILE* file, Book* const book);
