#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>

#include "sort.h"
#include "errors.h"

struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

static Node* createNode(const int key)
{
    Node* const newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->key = key;

    return newNode;
}

static ErrorCode insert(Node** const root, const int key)
{
    Node* newElement = createNode(key);
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
    }

    *root = newElement;

    return ok;
}

static void deleteTree(Node** const root)
{
    if (*root != NULL)
    {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}

static void inorderSort(const Node* const root, int* const array, size_t* const position)
{
    if (root != NULL)
    {
        inorderSort(root->left, array, position);
        array[(*position)++] = root->key;
        inorderSort(root->right, array, position);
    }
}

ErrorCode sortArray(int* const array, const size_t length)
{
    Node* tree = NULL;

    for (size_t i = 0; i < length; ++i)
    {
        if (insert(&tree, array[i]) == outOfMemory)
        {
            deleteTree(&tree);
            return outOfMemory;
        }
    }

    size_t position = 0;
    inorderSort(tree, array, &position);
    deleteTree(&tree);

    return ok;
}
