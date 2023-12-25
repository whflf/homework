#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "errors.h"

typedef struct Node Node;

// deletes tree
void deleteTree(Node** const root);

// prints tree
void printTree(const Node* const root, FILE* const file);

// calculates tree expression
int getResult(const Node* const root, bool* const isDivisionByZero);

// parses expression file and converts it to tree
Node* fileToTree(const char* const filename, ErrorCode* const error);
