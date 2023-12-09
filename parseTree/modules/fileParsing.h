#pragma once

#include "tree.h"
#include "stack.h"
#include "errors.h"

#define MAX_DIGITS_COUNT 8

Node* fileToTree(const char* const filename, ErrorCode* const error);
