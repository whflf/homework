#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "fileParsing.h"

static bool isOperation(const char token)
{
    return token == '+' || token == '-' || token == '*' || token == '/';
}

static ErrorCode addSubtreeToStack(Stack** const subtreeStack, const char token)
{
    Node* newSubtree = NULL;
    const char stringToken[2] = { token, '\0' };
    if (insert(&newSubtree, stringToken) == outOfMemory)
    {
        freeStack(subtreeStack);
        return outOfMemory;
    }

    if (push(subtreeStack, newSubtree) == outOfMemory)
    {
        freeStack(subtreeStack);
        deleteTree(&newSubtree);
        return outOfMemory;
    }

    return ok;
}

static Node* removeSubtreeFromStack(Stack** const subtreeStack)
{
    Node* const currentSubtree = top(*subtreeStack);
    pop(subtreeStack);
    Node* const treeToAddTo = top(*subtreeStack);
    if (treeToAddTo != NULL)
    {
        addSubtree(&treeToAddTo, &currentSubtree);
        return NULL;
    }
    else
    {
        return currentSubtree;
    }
}

static ErrorCode addNumberToParseTree(Stack** const subtreeStack, FILE* const file)
{
    char* const nodeValueTemp = (char*)calloc(MAX_DIGITS_COUNT + 1, sizeof(char));
    if (nodeValueTemp == NULL)
    {
        freeStack(subtreeStack);
        return outOfMemory;
    }

    int tmpValue = 0;
    if (fscanf(file, "%d", &tmpValue) != 1)
    {
        return fileParsingError;
    }
    itoa(tmpValue, nodeValueTemp, 10);
    char* const nodeValue = realloc(nodeValueTemp, strlen(nodeValueTemp) + 1);
    if (nodeValue == NULL)
    {
        free(nodeValueTemp);
        freeStack(subtreeStack);
        return outOfMemory;
    }

    Node* currentSubtree = top(*subtreeStack);
    if (insert(&currentSubtree, nodeValue) == outOfMemory)
    {
        free(nodeValue);
        freeStack(subtreeStack);
        return outOfMemory;
    }

    free(nodeValue);
    return ok;
}

Node* fileToTree(const char* const filename, ErrorCode* const error)
{
    *error = ok;

    FILE* const file = fopen(filename, "r");
    if (file == NULL)
    {
        *error = fileOpeningError;
        return NULL;
    }

    Stack* subtreeStack = NULL;
    while (!feof(file))
    {
        const char token = getc(file);
        if (isOperation(token))
        {
            if ((*error = addSubtreeToStack(&subtreeStack, token)) == outOfMemory) return NULL;
        }

        else if (token == ')')
        {
            Node* const finalTree = removeSubtreeFromStack(&subtreeStack);
            if (finalTree != NULL) return finalTree;
        }

        else if (token != ' ' && token != '(')
        {
            ungetc(token, file);

            if ((*error = addNumberToParseTree(&subtreeStack, file)) != ok) return NULL;
        }
    }

    return NULL;
}
