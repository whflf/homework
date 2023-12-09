#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

ErrorCode insert(Node** const root, const char* const value)
{
    char* const valueCopy = calloc(strlen(value) + 1, sizeof(char));
    if (valueCopy == NULL)
    {
        return outOfMemory;
    }

    strcpy(valueCopy, value);

    Node* newElement = createNode(valueCopy);
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

    *root = newElement;

    return ok;
}

void addSubtree(Node* const* const root, Node* const* const subtree)
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

size_t sizeOfTree(const Node* const root)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    return sizeOfTree(root->left) + sizeOfTree(root->right) + 1;
}

static bool isOperation(const char* const value)
{
    return value[0] == '+' || value[0] == '-' || value[0] == '*' || value[0] == '/';
}

void printTree(const Node* const root, FILE* const file)
{
    fprintf(file, "( %s ", root->value);
    const Node* const children[] = { root->left, root->right };
    for (size_t i = 0; i < sizeof(children) / sizeof(children[0]); ++i)
    {
        if (isOperation(children[i]->value))
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

int getResult(const Node* const root)
{
    switch (root->value[0])
    {
    case '+':
        return getResult(root->left) + getResult(root->right);
    case '-':
        return getResult(root->left) - getResult(root->right);
    case '*':
        return getResult(root->left) * getResult(root->right);
    case '/':
        return getResult(root->left) / getResult(root->right);
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
