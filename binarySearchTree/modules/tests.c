#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "errors.h"

static Node* initTestTree(void)
{
    Node* tree = NULL;

    const size_t treeSize = 6;
    const indexes[] = { 8, 3, 10, 1, 6, 14 };
    const char* const animals[] = { "cat", "dog", "fox", "mouse", "horse", "snake" };

    for (size_t i = 0; i < treeSize; ++i)
    {
        if (insert(&tree, indexes[i], animals[i]) != ok)
        {
            deleteTree(&tree);
            return NULL;
        }
    }

    return tree;
}

static bool testGettingValue(void)
{
    Node* tree = initTestTree();
    const char* const testValue = value(tree, 6);
    if (tree == NULL || testValue == NULL)
    {
        return false;
    }

    const bool result = strcmp(testValue, "horse") == 0;
    deleteTree(&tree);
    return result;
}

static bool testInserting(void)
{
    Node* tree = initTestTree();
    const char* const testValue = value(tree, 4);
    if (tree == NULL || !testGettingValue() || insert(&tree, 4, "cow") != ok || testValue == NULL)
    {
        return false;
    }

    const bool result = strcmp(testValue, "cow") == 0;
    deleteTree(&tree);
    return result;
}

static bool testDeleting(void)
{
    Node* tree = initTestTree();
    if (tree == NULL || !testGettingValue())
    {
        return false;
    }

    deleteNode(&tree, 4);
    const bool result = value(tree, 4) == NULL;
    deleteTree(&tree);
    return result;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
