#define _CRT_RAND_S

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#include "tree.h"
#include "errors.h"

#define STRING_LENGTH 10
#define STRING_NUMBER 200000

static char* generateString(const size_t length)
{
    const char* const characters = "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm0123456789/*-+=/.,?!()_";
    const size_t charactersLength = strlen(characters);
    char* const randomString = (char*)calloc(length + 1, sizeof(char));
    if (randomString == NULL)
    {
        return NULL;
    }

    unsigned int value = 0;
    for (size_t i = 0; i < length; ++i)
    {
        rand_s(&value);
        randomString[i] = characters[(size_t)((double)value / ((double)UINT_MAX + 1) * charactersLength)];
    }

    return randomString;
}

static void freeStringArray(char* const* const array, const size_t upperIndex)
{
    for (size_t i = 0; i < upperIndex; ++i)
    {
        free(array[i]);
    }
    free(array);
}

static char** getRandomStringArray(void)
{
    char** const strings = (char**)calloc(STRING_NUMBER, sizeof(char*));
    if (strings == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < STRING_NUMBER; ++i)
    {
        strings[i] = generateString(STRING_LENGTH);
        if (strings[i] == NULL)
        {
            freeStringArray(strings, i);
            return NULL;
        }
    }

    return strings;
}

static bool loadTest(void)
{
    const char* const* const keysAndValues = getRandomStringArray();
    if (keysAndValues == NULL)
    {
        return false;
    }

    Node* tree = NULL;
    clock_t start = clock();

    for (size_t i = 0; i < STRING_NUMBER; i += 2)
    {
        if ((tree = insert(tree, keysAndValues[i], keysAndValues[i + 1])) == NULL)
        {
            deleteTree(&tree);
            freeStringArray(keysAndValues, STRING_NUMBER);
            return false;
        }
    }

    for (size_t i = 0; i < STRING_NUMBER; i += 2)
    {
        tree = deleteNode(tree, keysAndValues[i]);
    }

    clock_t stop = clock();
    return (double)(stop - start) / CLOCKS_PER_SEC <= 5.0;
}

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
    if (tree == NULL)
    {
        return false;
    }

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
    if (tree == NULL)
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
    if (tree == NULL)
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
    return loadTest() && testGettingValue() && testInserting() && testDeleting();
}
