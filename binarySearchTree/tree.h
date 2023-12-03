#pragma once

#include <stdbool.h>

#include "errors.h"

typedef struct Node Node;

//adds value to tree with given key
ErrorCode insert(Node** root, const int key, const char* const value);

//gets value from tree by key
char* value(Node* const root, const int key);

//checks for a key in tree
bool isInDictionary(Node* const root, const int key);

//deletes certain node from tree by key
void deleteNode(Node** root, const int key);

//deletes tree
void deleteTree(Node** root);
