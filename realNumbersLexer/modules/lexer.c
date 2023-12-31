#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

typedef enum
{
    stateStart,
    stateIntegerPart,
    stateFractionalPart,
    stateExponent,
    stateDigitsAfterExp,
    stateIsNumber,
    stateIsNotNumber
} State;

static bool isExpSign(const char character)
{
    return character == 'E' || character == 'e';
}

static void checkCaseStart(State* const currentState, const char character)
{
    if (isdigit(character))
    {
        *currentState = stateIntegerPart;
    }
    else
    {
        *currentState = stateIsNotNumber;
    }
}

static void checkCaseIntegerPart(State* const currentState, const char character)
{
    if (character == '.')
    {
        *currentState = stateFractionalPart;
    }
    else if (isExpSign(character))
    {
        *currentState = stateExponent;
    }
    else if (!isdigit(character))
    {
        *currentState = stateIsNotNumber;
    }
}

static void checkCaseFractionalPart(State* const currentState, const char character)
{
    if (isExpSign(character))
    {
        *currentState = stateExponent;
    }
    else if (!isdigit(character))
    {
        *currentState = stateIsNotNumber;
    }
}

static void checkCaseExponent(State* const currentState, const char character)
{
    if (isdigit(character) || character == '+' || character == '-')
    {
        *currentState = stateDigitsAfterExp;
    }
    else
    {
        *currentState = stateIsNotNumber;
    }
}

static void checkCaseDigitsAfterExp(State* const currentState, const char character)
{
    if (!isdigit(character))
    {
        *currentState = stateIsNotNumber;
    }
}

static State analyzeString(const char* const string)
{
    const size_t stringLength = strlen(string);
    if (stringLength == 0)
    {
        return stateIsNotNumber;
    }

    State currentState = stateStart;
    for (size_t i = 0; i < stringLength; ++i)
    {
        switch (currentState)
        {
        case stateStart:
            checkCaseStart(&currentState, string[i]);
            break;
        case stateIntegerPart:
            checkCaseIntegerPart(&currentState, string[i]);
            break;
        case stateFractionalPart:
            checkCaseFractionalPart(&currentState, string[i]);
            break;
        case stateExponent:
            checkCaseExponent(&currentState, string[i]);
            break;
        case stateDigitsAfterExp:
            checkCaseDigitsAfterExp(&currentState, string[i]);
            break;
        }

        if (currentState == stateIsNotNumber)
        {
            return currentState;
        }
    }

    return stateIsNumber;
}

bool isNumber(const char* const string)
{
    return analyzeString(string) == stateIsNumber;
}
