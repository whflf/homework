#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "tree.h"
#include "errors.h"

struct Node
{
    char* key;
    char* value;
    unsigned int height;
    int difference;
    Node* left;
    Node* right;
};

typedef enum
{
    fromLeft,
    fromRight
} NodeUpdatingOption;

static char* copyString(const char* const string)
{
    char* const stringCopy = (char*)calloc(strlen(string) + 1, sizeof(char));
    if (stringCopy == NULL)
    {
        return NULL;
    }

    strcpy(stringCopy, string);

    return stringCopy;
}

static Node* createNode(const char* const key, const char* const value)
{
    Node* const newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    char* const keyCopy = copyString(key);
    if (keyCopy == NULL)
    {
        free(newNode);
        return NULL;
    }

    char* const valueCopy = copyString(value);
    if (valueCopy == NULL)
    {
        free(newNode);
        free(keyCopy);
        return NULL;
    }

    newNode->key = keyCopy;
    newNode->value = valueCopy;

    return newNode;
}

static void freeNode(Node* const root)
{
    free(root->key);
    free(root->value);
    free(root);
}

static int getHeight(const Node* const node)
{
    return node == NULL ? -1 : node->height;
}

static void updateHeight(Node* const node)
{
    const int leftHeight = getHeight(node->left),
        rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static void updateDifference(Node* const node)
{
    node->difference = getHeight(node->left) - getHeight(node->right);
}

static Node* rotateLeft(Node* const a)
{
    Node* const b = a->right;
    Node* const c = b->left;
    b->left = a;
    a->right = c;

    updateHeight(a);
    updateHeight(b);

    updateDifference(a);
    updateDifference(b);

    return b;
}

static Node* rotateRight(Node* const a)
{
    Node* const b = a->left;
    Node* const c = b->right;
    b->right = a;
    a->left = c;

    updateHeight(a);
    updateHeight(b);

    updateDifference(a);
    updateDifference(b);

    return b;
}

static Node* bigRotateLeft(Node* a)
{
    a->right = rotateRight(a->right);
    a = rotateLeft(a);

    return a;
}

static Node* bigRotateRight(Node* a)
{
    a->left = rotateLeft(a->left);
    a = rotateRight(a);

    return a;
}

static Node* balance(Node* root)
{
    if (root->difference == -2)
    {
        if (root->right != NULL && root->right->difference <= 0)
        {
            return rotateLeft(root);
        }
        return bigRotateLeft(root);
    }

    if (root->difference == 2)
    {
        if (root->left != NULL && root->left->difference >= 0)
        {
            return rotateRight(root);
        }
        return bigRotateRight(root);
    }

    return root;
}

Node* insert(Node* root, const char* const key, const char* const value)
{
    if (root == NULL)
    {
        Node* newElement = createNode(key, value);
        return newElement;
    }

    if (strcmp(key, root->key) < 0)
    {
        Node* const temp = insert(root->left, key, value);
        if (temp == NULL)
        {
            return NULL;
        }

        root->left = temp;
        updateHeight(root);
        updateDifference(root);
    }
    else if (strcmp(key, root->key) > 0)
    {
        Node* const temp = insert(root->right, key, value);
        if (temp == NULL)
        {
            return NULL;
        }

        root->right = temp;
        updateHeight(root);
        updateDifference(root);
    }
    else
    {
        char* temp = root->value;

        char* const valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            return NULL;
        }

        root->value = valueCopy;
        free(temp);

        return root;
    }

    return balance(root);
}

static Node* search(Node* const root, const char* const key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (strcmp(root->key, key) == 0)
    {
        return root;
    }
    if (strcmp(key, root->key) < 0)
    {
        return search(root->left, key);
    }
    if (strcmp(key, root->key) > 0)
    {
        return search(root->right, key);
    }

    return NULL;
}

const char* value(Node* const root, const char* const key)
{
    const Node* const element = search(root, key);
    if (element != NULL)
    {
        return element->value;
    }

    return NULL;
}

bool isInDictionary(Node* const root, const char* const key)
{
    return search(root, key) != NULL;
}

static Node* mostLeft(Node* element)
{
    if (element->left == NULL)
    {
        return element;
    }

    if (element->left->left == NULL)
    {
        Node* const mostLeftNode = element->left;
        element->left = element->left->right;
        updateHeight(element);
        updateDifference(element);
        element = balance(element);

        return mostLeftNode;
    }

    Node* const mostLeftNode = mostLeft(element->left);
    updateHeight(element);
    updateDifference(element);
    element = balance(element);

    return mostLeftNode;
}

Node* deleteNode(Node* root, const char* const key)
{
    if (strcmp(root->key, key) == 0)
    {
        if (root->left == NULL && root->right == NULL)
        {
            freeNode(root);
            return NULL;
        }

        else if (root->left == NULL || root->right == NULL)
        {
            if (root->left == NULL)
            {
                Node* const oldRoot = root;
                root = root->right;
                freeNode(oldRoot);

                return root;
            }
            else
            {
                Node* const oldRoot = root;
                root = root->left;
                freeNode(oldRoot);

                return root;
            }
        }

        else
        {
            Node* const oldRoot = root;
            root = mostLeft(root->right);
            root->left = oldRoot->left;
            root->right = oldRoot->right;
            freeNode(oldRoot);

            updateHeight(root);
            updateDifference(root);

            return balance(root);
        }
    }

    if (strcmp(key, root->key) < 0)
    {
        root->left = deleteNode(root->left, key);
        updateHeight(root);
        updateDifference(root);
    }
    else if (strcmp(key, root->key) > 0)
    {
        root->right = deleteNode(root->right, key);
        updateHeight(root);
        updateDifference(root);
    }

    return balance(root);
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
