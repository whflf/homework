#pragma once

#include <stdbool.h>

#include "errors.h"

typedef struct Node Node;

//adds value to tree with given key
Node* insert(Node* const root, const char* const key, const char* const value);

//gets value from tree by key
const char* value(Node* const root, const char* const key);

//checks for a key in tree
bool isInDictionary(Node* const root, const char* const key);

//deletes certain node from tree by key
Node* deleteNode(Node* root, const char* const key);

//deletes tree
void deleteTree(Node** const root);
