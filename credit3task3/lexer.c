#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

#define CHARACTERS_BEFORE_AT_SIGN "QWERTYUIOPASDFGHJKLZXCVBNM1234567890._%+-"
#define CHARACTERS_AFTER_AT_SIGN "QWERTYUIOPASDFGHJKLZXCVBNM1234567890"
#define UPPERCASE_LETTERS "QWERTYUIOPASDFGHJKLZXCVBNM"

typedef enum
{
    start,
    charactersBeforeAtSign,
    atSign,
    charactersAfterAtSign,
    dotSign,
    finalLetters
} State;

static bool isValid(const char character, const char* const correctCharacters)
{
    const correctCharactersCount = strlen(correctCharacters);

    for (size_t i = 0; i < correctCharactersCount; ++i)
    {
        if (character == correctCharacters[i])
        {
            return true;
        }
    }

    return false;
}

static State analyzeString(const char* const string)
{
    State currentState = start;
    const size_t length = strlen(string);

    for (size_t i = 0; i < length; ++i)
    {
        switch (currentState)
        {
        case start:
            if (isValid(string[i], CHARACTERS_BEFORE_AT_SIGN))
            {
                currentState = charactersBeforeAtSign;
            }
            break;
        case charactersBeforeAtSign:
            if (string[i] == '@')
            {
                currentState = atSign;
            }
            else if (!isValid(string[i], CHARACTERS_BEFORE_AT_SIGN))
            {
                return currentState;
            }
            break;
        case atSign:
            if (isValid(string[i], CHARACTERS_AFTER_AT_SIGN))
            {
                currentState = charactersAfterAtSign;
                continue;
            }
            return currentState;
        case charactersAfterAtSign:
            if (string[i] == '.')
            {
                currentState = dotSign;
            }
            else if (!isValid(string[i], CHARACTERS_AFTER_AT_SIGN))
            {
                return currentState;
            }
            break;
        case dotSign:
            if (isValid(string[i], UPPERCASE_LETTERS))
            {
                currentState = finalLetters;
                continue;
            }
            else if (isdigit(string[i]))
            {
                currentState = charactersAfterAtSign;
                continue;
            }
            return currentState;
        case finalLetters:
            if (string[i] == '.')
            {
                currentState = dotSign;
            }
            else if (isdigit(string[i]))
            {
                currentState = charactersAfterAtSign;
            }
        }
    }

    return currentState;
}

bool isCorrect(const char* const string)
{
    return analyzeString(string) == finalLetters;
}
