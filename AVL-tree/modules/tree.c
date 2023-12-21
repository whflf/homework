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
    int difference;
    Node* left;
    Node* right;
};

typedef enum
{
    fromLeft,
    fromRight
} NodeUpdatingOption;

static Node* createNode(char* const key, char* const value)
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
    free(root->key);
    free(root->value);
    free(root);
}

static unsigned int calcHeight(const Node* const node)
{
    if (node == NULL)
    {
        return 0;
    }

    unsigned int leftHeight = calcHeight(node->left),
                 rightHeight = calcHeight(node->right);
    return (leftHeight >= rightHeight ? leftHeight : rightHeight) + 1;
}

static Node* rotateLeft(Node* const a)
{
    Node* const b = a->right;
    Node* const c = b->left;
    b->left = a;
    a->right = c;

    unsigned int leftHeight = calcHeight(a->left),
                 rightHeight = calcHeight(a->right);

    a->difference = leftHeight - rightHeight;
    b->difference = (leftHeight >= rightHeight ? leftHeight : rightHeight) + 1 - calcHeight(b->right);

    return b;
}

static Node* rotateRight(Node* const a)
{
    Node* const b = a->left;
    Node* const c = b->right;
    b->right = a;
    a->left = c;

    unsigned int leftHeight = calcHeight(a->left),
        rightHeight = calcHeight(a->right);

    a->difference = leftHeight - rightHeight;
    b->difference = calcHeight(b->left) - (leftHeight >= rightHeight ? leftHeight : rightHeight) - 1;

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
        if (root->right->difference <= 0)
        {
            return rotateLeft(root);
        }
        return bigRotateLeft(root);
    }

    if (root->difference == 2)
    {
        if (root->right->difference >= 0)
        {
            return rotateRight(root);
        }
        return bigRotateRight(root);
    }

    return root;
}

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

static bool isRefreshed(const Node* const oldNode, const Node* const newNode)
{
    if (oldNode != NULL && strcmp(oldNode->value, newNode->value) != 0)
    {
        return true;
    }

    return false;
}

static Node* insertionNodeUpdate(Node* root, const NodeUpdatingOption option, const char* const key, const char* const value)
{
    Node* const oldChild = option == fromLeft ? root->left : root->right;
    const int oldDifference = oldChild != NULL ? oldChild->difference : 0;

    Node* newChild = NULL;
    if (option == fromLeft)
    {
        root->left = insert(root->left, key, value);
        if (root->left == NULL)
        {
            return NULL;
        }
        newChild = root->left;
    }
    else
    {
        root->right = insert(root->right, key, value);
        if (root->right == NULL)
        {
            return NULL;
        }
        newChild = root->right;
    }

    if (oldChild == NULL || !isRefreshed(oldChild, newChild)
        && newChild->difference != 0 && oldDifference != newChild->difference)
    {
        root->difference = option == fromLeft ? root->difference + 1 : root->difference - 1;
    }

    return root;
}

Node* insert(Node* root, const char* const key, const char* const value)
{
    if (root == NULL)
    {
        char* const keyCopy = copyString(key);
        if (keyCopy == NULL)
        {
            return NULL;
        }

        char* const valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            free(keyCopy);
            return NULL;
        }

        Node* newElement = createNode(keyCopy, valueCopy);
        if (newElement == NULL)
        {
            free(keyCopy);
            free(valueCopy);
        }

        return newElement;
    }

    if (strcmp(key, root->key) < 0)
    {
        root = insertionNodeUpdate(root, fromLeft, key, value);
        if (root == NULL)
        {
            return NULL;
        }
    }
    else if (strcmp(key, root->key) > 0)
    {
        root = insertionNodeUpdate(root, fromRight, key, value);
        if (root == NULL)
        {
            return NULL;
        }
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

static Node* mostLeft(const Node* const element)
{
    Node* temp = element;
    for (; temp->left != NULL; temp = temp->left);

    return temp;
}

static void deletionNodeUpdate(Node* root, const NodeUpdatingOption option, const char* const key)
{
    const int oldDifference = option == fromLeft ? root->left->difference : root->right->difference;

    Node* newChild = NULL;
    if (option == fromLeft)
    {
        root->left = deleteNode(root->left, key);
        newChild = root->left;
    }
    else
    {
        root->right = deleteNode(root->right, key);
        newChild = root->right;
    }

    if (newChild == NULL || newChild->difference == 0 && oldDifference != newChild->difference)
    {
        root->difference = option == fromLeft ? root->difference - 1 : root->difference + 1;
    }
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
            Node* const successor = mostLeft(root->right);

            root->key = copyString(successor->key);
            if (root->key == NULL)
            {
                return NULL;
            }

            root->value = copyString(successor->value);
            if (root->value == NULL)
            {
                free(root->key);
                return NULL;
            }

            deletionNodeUpdate(root, fromRight, successor->key);

            return balance(root);
        }
    }

    if (strcmp(key, root->key) < 0)
    {
        deletionNodeUpdate(root, fromLeft, key);
    }
    else if (strcmp(key, root->key) > 0)
    {
        deletionNodeUpdate(root, fromRight, key);
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
