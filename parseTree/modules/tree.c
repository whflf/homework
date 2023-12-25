#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"

struct Node
{
    char* value;
    Node* left;
    Node* right;
};

static Node* createNode(char* const value)
{
    Node* const newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->value = value;
    return newNode;
}

static ErrorCode insert(Node** const root, const char* const value)
{
    char* const valueCopy = calloc(strlen(value) + 1, sizeof(char));
    if (valueCopy == NULL)
    {
        return outOfMemory;
    }

    strcpy(valueCopy, value);

    Node* const newElement = createNode(valueCopy);
    if (newElement == NULL)
    {
        return outOfMemory;
    }

    if (*root != NULL)
    {
        if ((*root)->left == NULL)
        {
            (*root)->left = newElement;
        }
        else
        {
            (*root)->right = newElement;
        }
    }
    else
    {
        *root = newElement;
    }

    return ok;
}

static void addSubtree(Node* const* const root, Node* const* const subtree)
{
    if ((*root)->left == NULL)
    {
        (*root)->left = *subtree;
    }
    else
    {
        (*root)->right = *subtree;
    }
}

static bool isOperation(const char value)
{
    return value == '+' || value == '-' || value == '*' || value == '/';
}

void printTree(const Node* const root, FILE* const file)
{
    fprintf(file, "( %s ", root->value);
    const Node* const children[] = { root->left, root->right };
    for (size_t i = 0; i < sizeof(children) / sizeof(children[0]); ++i)
    {
        if (isOperation(children[i]->value[0]))
        {
            printTree(children[i], file);
        }
        else
        {
            fprintf(file, "%s ", children[i]->value);
        }
    }
    fprintf(file, ") ");
}

int getResult(const Node* const root, bool* const isDivisionByZero)
{
    *isDivisionByZero = false;
    int resultLeft = 0, resultRight = 0;
    if (root->left != NULL && root->right != NULL)
    {
        resultLeft = getResult(root->left, isDivisionByZero),
            resultRight = getResult(root->right, isDivisionByZero);
    }

    switch (root->value[0])
    {
    case '+':
        return resultLeft + resultRight;
    case '-':
        return resultLeft - resultRight;
    case '*':
        return resultLeft * resultRight;
    case '/':
        if (resultRight == 0)
        {
            *isDivisionByZero = true;
            return -1;
        }
        return resultLeft / resultRight;
    default:
        return atoi(root->value);
    }
}

void deleteTree(Node** const root)
{
    if (*root != NULL)
    {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        free((*root)->value);
        free(*root);
        *root = NULL;
    }
}

static ErrorCode insertNumberToTree(Node** const root, const int number)
{
    char* const nodeValue = (char*)calloc(_MAX_ITOSTR_BASE10_COUNT, sizeof(char));
    if (nodeValue == NULL)
    {
        return outOfMemory;
    }

    itoa(number, nodeValue, 10);
    if (insert(root, nodeValue) == outOfMemory)
    {
        free(nodeValue);
        return outOfMemory;
    }

    free(nodeValue);
    return ok;
}

static ErrorCode parseExpression(FILE* const file, Node** currentTree)
{
    if (feof(file))
    {
        return ok;
    }

    char token = getc(file);
    if (token == '(')
    {
        char operator;
        for (operator = getc(file); !isOperation(operator); operator = getc(file));

        Node* newTree = NULL;

        const char operatorString[2] = { operator, '\0' };
        insert(&newTree, operatorString);

        ErrorCode error = ok;
        parseExpression(file, &newTree);

        if (*currentTree != NULL)
        {
            addSubtree(currentTree, &newTree);
        }

        if (*currentTree == NULL)
        {
            *currentTree = newTree;
        }
    }
    else if (token == ')')
    {
        return ok;
    }
    else if (isdigit(token))
    {
        ungetc(token, file);

        int a = 0, b = 0;
        switch (fscanf(file, "%d%d%*[^)])", &a, &b))
        {
        case 2:
            insertNumberToTree(currentTree, a);
            insertNumberToTree(currentTree, b);
            break;
        case 1:
            insertNumberToTree(currentTree, a);
            if ((token = getc(file)) == '(')
            {
                ungetc(token, file);
                parseExpression(file, currentTree);
            }
            break;
        default:
            return fileParsingError;
        }

        return ok;
    }
    return parseExpression(file, currentTree);
}

Node* fileToTree(const char* const filename, ErrorCode* const error)
{
    FILE* const file = fopen(filename, "r");
    if (file == NULL)
    {
        *error = fileOpeningError;
        return NULL;
    }

    Node* parsedTree = NULL;

    *error = parseExpression(file, &parsedTree);

    fclose(file);
    return parsedTree;
}
