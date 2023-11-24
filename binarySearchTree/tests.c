#include <stdlib.h>

#include "tree.h"
#include "errors.h"

static Node* testTree(void)
{
    Node* tree = NULL;
    insert(&tree, 8, "cat");
    insert(&tree, 3, "dog");
    insert(&tree, 10, "fox");
    insert(&tree, 1, "mouse");
    insert(&tree, 6, "horse");
    insert(&tree, 14, "snake");
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
