#include <stdlib.h>
#include <stdbool.h>

#include "include/tree.h"
#include "include/errors.h"

static Node* testTree(void)
{
    Node* tree = NULL;

    const indexes[] = {8, 3, 10, 1, 6, 14};
    const char* const animals[] = { "cat", "dog", "fox", "mouse", "horse", "snake" };

    return tree;
}

static bool testGettingValue(void)
{
    Node* tree = testTree();

    return value(tree, 6) == "horse";
}

static bool testInserting(void)
{
    Node* tree = testTree();

    if (testGettingValue())
    {
        insert(&tree, 4, "cow");
        return value(tree, 4) == "cow";
    }

    return false;
}

static bool testDeleting(void)
{
    Node* tree = testTree();

    if (testGettingValue())
    {
        deleteNode(&tree, 4);
        return value(tree, 4) == NULL;
    }

    return false;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
