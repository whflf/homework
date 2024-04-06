#pragma once

#include "list.h"
#include "errors.h"

// reads file and writes its content to a memory
ErrorCode readFile(const char* const filename, char** const content, size_t* const fileSize);

// parses file content and fills structure
ErrorCode deserializeBookContent(const char* const content, List** book);
