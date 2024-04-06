#include <stdlib.h>
#include <stdbool.h>

#include "include/stack.h"
#include "include/errors.h"
#include "brackets.h"

static char getBracketOpposition(char bracket)
{
    char bracketPairs[][2] = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
        {'<', '>'}
    };

    for (size_t i = 0; i < countof(bracketPairs); ++i)
    {
        if (bracket == bracketPairs[i][0])
        {
            return bracketPairs[i][1];
        }
        else if (bracket == bracketPairs[i][1])
        {
            return bracketPairs[i][0];
        }
    }

    return '0';
}

bool parenthesisCheck(const char* const string, ErrorCode* errorCode)
{
    Stack* parenthesisStack = NULL;

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == '(' || string[i] == '{' || string[i] == '[' || string[i] == '<')
        {
            if ((*errorCode = push(&parenthesisStack, string[i])) != ok)
            {
                freeStack(&parenthesisStack);
                return false;
            }
        }
        else if (string[i] == ')' || string[i] == '}' || string[i] == ']' || string[i] == '>')
        {
            const char previousParenthesis = pop(&parenthesisStack, errorCode);
            if (*errorCode != ok || previousParenthesis != getBracketOpposition(string[i]))
            {
                freeStack(&parenthesisStack);
                return false;
            }
        }
    }

    pop(&parenthesisStack, errorCode);
    freeStack(&parenthesisStack);
    return *errorCode == stackIsEmpty;
}