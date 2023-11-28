#include <stdlib.h>
#include <stdbool.h>

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

static Node* createNode(const int key, const char* const value)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));

    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->key = key;
    newNode->value = value;

    return newNode;
}

ErrorCode insert(Node** root, const int key, const char* const value)
{
    Node* newElement = createNode(key, value);

    if (newElement == NULL)
    {
        return outOfMemory;
    }

    while (*root != NULL)
    {
        if (key < (*root)->key)
        {
            if ((*root)->left != NULL)
            {
                root = &(*root)->left;
            }
            else
            {
                newElement->parent = *root;
                (*root)->left = newElement;

                return ok;
            }
        }

        else if (key > (*root)->key)
        {
            if ((*root)->right != NULL)
            {
                root = &(*root)->right;
            }
            else
            {
                newElement->parent = *root;
                (*root)->right = newElement;

                return ok;
            }
        }
        else
        {
            char* tmp = (*root)->value;
            (*root)->value = value;
            free(tmp);
            tmp = NULL;

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
}

char* value(Node* const root, const int key)
{
    Node* element = search(root, key);

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

static Node* next(Node* element)
{
    if (element->left == NULL)
    {
        return element;
    }

    return next(element->left);
}

void deleteNode(Node**  root, const int key)
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
        Node* parent = element->parent;

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
                Node* elementCopy = element;
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
            element = NULL;
        }

        else
        {
            Node* successor = next(element->right);
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
            successor = NULL;
        }
    }
}

void deleteTree(Node** root)
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
