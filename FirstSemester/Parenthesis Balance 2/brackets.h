#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "include/errors.h"

#define countof(array) sizeof(array) / sizeof(array[0])

bool parenthesisCheck(const char* const string, ErrorCode* errorCode);
