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

static Node* search(const Node* const root, const int key)
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

char* value(Node* const root, const int key)
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

static Node* next(const Node* const element)
{
    if (element->left == NULL)
    {
        return element;
    }

    return next(element->left);
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

    if (element != NULL)
    {
        Node* const parent = element->parent;

        if (element->left == NULL && element->right == NULL)
        {
            if (parent != NULL)
            {
                if (parent->left == element)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            else
            {
                Node* const elementCopy = element;
                *root = NULL;
                free(elementCopy->value);
                free(elementCopy);
                return;
            }
            free(element->value);
            free(element);
        }

        else if (element->left == NULL || element->right == NULL)
        {
            if (element->left == NULL)
            {
                if (parent != NULL)
                {
                    if (parent->left == element)
                    {
                        parent->left = element->right;
                    }
                    else
                    {
                        parent->right = element->right;
                    }
                }
                element->right->parent = parent;
            }
            else
            {
                if (parent != NULL)
                {
                    if (parent->left == element)
                    {
                        parent->left = element->left;
                    }
                    else
                    {
                        parent->right = element->left;
                    }
                }
                element->left->parent = parent;
            }

            free(element->value);
            free(element);
        }

        else
        {
            Node* const successor = next(element->right);
            element->key = successor->key;
            element->value = successor->value;
            if (successor == successor->parent->left)
            {
                successor->parent->left = successor->right;
            }
            else
            {
                successor->parent->right = successor->right;
            }
            if (successor->right != NULL)
            {
                successor->right->parent = successor->parent;
            }

            free(successor);
        }
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
