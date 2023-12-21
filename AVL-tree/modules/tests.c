#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "errors.h"

static Node* initTestTree(void)
{
    Node* tree = NULL;

    const size_t treeSize = 6;
    const char* const animals[] = { "cat", "dog", "fox", "horse", "mouse", "snake" };
    const char* const names[] = { "Tom", "Hachiko", "Nick", "Applejack", "Jerry", "Kaa" };

    for (size_t i = 0; i < treeSize; ++i)
    {
        if ((tree = insert(tree, animals[i], names[i])) == NULL)
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
    const char* const testValue = value(tree, "fox");
    if (tree == NULL || testValue == NULL)
    {
        return false;
    }

    const bool result = strcmp(testValue, "Nick") == 0;
    deleteTree(&tree);
    return result;
}

static bool testInserting(void)
{
    Node* tree = initTestTree();
    if (tree == NULL || !testGettingValue())
    {
        return false;
    }

    tree = insert(tree, "rabbit", "Judy");
    const char* const testValue = value(tree, "rabbit");
    if (tree == NULL || testValue == NULL)
    {
        deleteTree(&tree);
        return false;
    }

    const bool result = strcmp(testValue, "Judy") == 0;
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

    tree = deleteNode(tree, "dog");
    const bool result = value(tree, "dog") == NULL;
    deleteTree(&tree);
    return result;
}

bool passTests(void)
{
    return testInserting() && testDeleting();
}
