#include <stdlib.h>
#include <string.h>

#include "include/tree.h"
#include "include/errors.h"

static Node* testTree(void)
{
    Node* tree = NULL;

    const size_t treeSize = 6;
    const indexes[] = {8, 3, 10, 1, 6, 14};
    const char* const animals[] = { "cat", "dog", "fox", "mouse", "horse", "snake" };

    for (size_t i = 0; i < treeSize; ++i)
    {
        if (insert(&tree, indexes[i], animals[i]) != ok)
        {
            return NULL;
        }
    }

    return tree;
}

static bool testGettingValue(void)
{
    Node* tree = testTree();

    if (tree != NULL)
    {
        const bool result = strcmp(value(tree, 6), "horse") == 0;
        deleteTree(&tree);
        return result;
    }

    return false;
}

static bool testInserting(void)
{
    Node* tree = testTree();

    if (tree != NULL && testGettingValue() && insert(&tree, 4, "cow") == ok)
    {
        const bool result = strcmp(value(tree, 4), "cow") == 0;
        deleteTree(&tree);
        return result;
    }

    return false;
}

static bool testDeleting(void)
{
    Node* tree = testTree();

    if (tree != NULL && testGettingValue())
    {
        deleteNode(&tree, 4);
        const bool result = value(tree, 4) == NULL;
        deleteTree(&tree);
        return result;
    }

    return false;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
