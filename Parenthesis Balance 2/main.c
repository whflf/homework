#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

#define LENGTH 51

#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

bool parenthesisCheck(char* const string)
{
    const int errorCode = ok;
    Stack* const parenthesisStack = createStack();
    size_t i = 0;
    while (string[i] != '\n')
    {
        if (string[i] == '(' || string[i] == '{' || string[i] == '[') 
        {
            push(&parenthesisStack, string[i]);
        }
        if (string[i] == ')') {
            const char previousParenthesis = top(parenthesisStack, &errorCode);
            if (previousParenthesis != '(') 
            {
                return 0;
            }
            pop(&parenthesisStack);
        }
        if (string[i] == ']') {
            const char previousParenthesis = top(parenthesisStack, &errorCode);
            if (previousParenthesis != '[')
            {
                return 0;
            }
            pop(&parenthesisStack);
        }
        if (string[i] == '}') {
            const char previousParenthesis = top(parenthesisStack, &errorCode);
            if (previousParenthesis != '{')
            {
                return 0;
            }
            pop(&parenthesisStack);
        }
        ++i;
    }

    const char stackValue = top(parenthesisStack, &errorCode);
    freeStack(&parenthesisStack);
    if (stackValue != '\0')
    {
        return 0;
    }
    return 1;
}

bool testCorrectCase()
{
    return parenthesisCheck("([{}])");
}

bool testIncorrectCase()
{
    return !parenthesisCheck("({)}");
}

int main()
{
    if (!testCorrectCase() || !testIncorrectCase()) 
    {
        printf("~ Tests failed");
        return TESTS_FAILED;
    }
    char* const string = (char*)malloc(LENGTH * sizeof(char));
    if (string == NULL) {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }
    printf("Enter a string (up to 50 symbols): ");
    fgets(string, LENGTH, stdin);

    printf("%s", parenthesisCheck(string) ? "true" : "false");
}
