#pragma once

#include <stdbool.h>

#include "errors.h"

typedef struct Node Node;

// sorts given array
ErrorCode sortArray(int* const array, const size_t length);
