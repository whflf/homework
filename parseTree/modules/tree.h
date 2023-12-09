#pragma once

#include <stdio.h>
#include "errors.h"

typedef struct Node Node;

// adds value to tree with given key
ErrorCode insert(Node** const root, const char* const value);

// adds another parse tree to tree
void addSubtree(Node** const root, Node* const* const subtree);

// deletes tree
void deleteTree(Node** const root);

// prints tree
void printTree(const Node* const root, FILE* const file);

// calculates tree expression
int getResult(const Node* const root);
