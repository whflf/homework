#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "tree.h"
#include "errors.h"

struct Node
{
    int key;
    char* value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

static Node* createNode(const int key, char* const value)
{
    Node* const newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->key = key;
    newNode->value = value;

    return newNode;
}

static void freeNode(Node* const root)
{
    free(root->value);
    free(root);
}

ErrorCode insert(Node** const root, const int key, const char* const value)
{
    char* const valueCopy = calloc(strlen(value) + 1, sizeof(char));
    if (valueCopy == NULL)
    {
        return outOfMemory;
    }

    strcpy(valueCopy, value);

    Node* newElement = createNode(key, valueCopy);
    if (newElement == NULL)
    {
        free(valueCopy);
        return outOfMemory;
    }

    Node* tmpRoot = *root;
    while (tmpRoot != NULL)
    {
        if (key < tmpRoot->key)
        {
            if (tmpRoot->left != NULL)
            {
                tmpRoot = tmpRoot->left;
            }
            else
            {
                newElement->parent = tmpRoot;
                tmpRoot->left = newElement;

                return ok;
            }
        }

        else if (key > tmpRoot->key)
        {
            if (tmpRoot->right != NULL)
            {
                tmpRoot = tmpRoot->right;
            }
            else
            {
                newElement->parent = tmpRoot;
                tmpRoot->right = newElement;

                return ok;
            }
        }
        else
        {
            char* tmp = tmpRoot->value;
            tmpRoot->value = valueCopy;
            free(tmp);

            return ok;
        }
    }

    *root = newElement;

    return ok;
}

static Node* search(Node* const root, const int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->key == key)
    {
        return root;
    }
    if (key < root->key)
    {
        return search(root->left, key);
    }
    if (key > root->key)
    {
        return search(root->right, key);
    }
    return NULL;
}

const char* value(Node* const root, const int key)
{
    const Node* const element = search(root, key);
    if (element != NULL)
    {
        return element->value;
    }

    return NULL;
}

bool isInDictionary(Node* const root, const int key)
{
    return search(root, key) != NULL;
}

static Node* mostLeft(const Node* const element)
{
    if (element->left != NULL)
    {
        Node* temp = element->left;
        for (; temp->left != NULL; temp = temp->left);
        return temp;
    }

    return element;
}

static bool changeChild(Node* const parent, const Node* const oldChild, Node* const newChild)
{
    const bool parentIsNotNull = parent != NULL;
    if (parentIsNotNull)
    {
        if (parent->left == oldChild)
        {
            parent->left = newChild;
        }
        else
        {
            parent->right = newChild;
        }
        if (newChild != NULL)
        {
            newChild->parent = parent;
        }
    }
    return parentIsNotNull;
}

void deleteNode(Node** const root, const int key)
{
    Node* element = NULL;

    if ((*root)->key == key)
    {
        element = *root;
    }
    else
    {
        element = search(*root, key);
    }

    if (element == NULL)
    {
        return;
    }

    Node* const parent = element->parent;

    if (element->left == NULL && element->right == NULL)
    {
        if (!changeChild(parent, element, NULL))
        {
            Node* const elementCopy = element;
            *root = NULL;
            freeNode(elementCopy);
            return;
        }
        freeNode(element);
    }

    else if (element->left == NULL || element->right == NULL)
    {
        if (element->left == NULL)
        {
            if (!changeChild(parent, element, element->right))
            {
                *root = element->right;
            }
        }
        else
        {
            if (!changeChild(parent, element, element->left))
            {
                *root = element->left;
            }
        }

        freeNode(element);
    }
    else
    {
        Node* const successor = mostLeft(element->right);
        element->key = successor->key;
        element->value = successor->value;
        changeChild(successor->parent, successor, successor->right);

        free(successor);
    }
}

void deleteTree(Node** const root)
{
    if (*root != NULL)
    {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        freeNode(*root);
        *root = NULL;
    }
}
