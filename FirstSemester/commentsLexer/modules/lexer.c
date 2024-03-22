#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"

#define NUMBER_OF_CASES 3
#define NUMBER_OF_STATES 6

#define MIN_ALLOCATION_SIZE 16

typedef enum
{
    slash,
    asterisk,
    otherCharacters
} CharCase;

typedef enum
{
    stateStart,
    stateFirstSlash,
    stateFirstAsterisk,
    stateCommentContent,
    stateSecondAsterisk,
    stateSecondSlash
} State;

typedef struct Comment
{
    char* string;
    size_t maxSize;
    size_t currentSize;
} Comment;

State stateTable[NUMBER_OF_STATES][NUMBER_OF_CASES] = {
    //          /              *        other   
        {stateFirstSlash, stateStart, stateStart},                        // start
        {stateFirstSlash, stateFirstAsterisk, stateStart},                // firstSlash
        {stateCommentContent, stateSecondAsterisk, stateCommentContent},  // firstAsterisk
        {stateCommentContent, stateSecondAsterisk, stateCommentContent},  // commentContent
        {stateSecondSlash, stateSecondAsterisk, stateCommentContent},     // secondAsterisk
        {stateStart, stateStart, stateStart}                              // secondSlash
};

static void changeState(State* const state, const char character)
{
    switch (character)
    {
    case '/':
        *state = stateTable[*state][slash];
        break;
    case '*':
        *state = stateTable[*state][asterisk];
        break;
    default:
        *state = stateTable[*state][otherCharacters];
        break;
    }
}

static Comment* createComment(void)
{
    Comment* comment = (Comment*)calloc(1, sizeof(Comment));
    if (comment == NULL)
    {
        return NULL;
    }

    comment->string = (char*)calloc(MIN_ALLOCATION_SIZE, sizeof(char));
    if (comment->string == NULL)
    {
        free(comment);
        return NULL;
    }

    comment->maxSize = MIN_ALLOCATION_SIZE;
    return comment;
}

static void freeComment(Comment* const comment)
{
    free(comment->string);
    free(comment);
}

static ErrorCode addCharacterToCommentString(Comment* const comment, const char character)
{
    if (comment->currentSize == comment->maxSize - 2)
    {
        char* const temp = (char*)realloc(comment->string, comment->maxSize * 2);
        if (temp == NULL)
        {
            freeComment(comment);
            return outOfMemory;
        }

        comment->string = temp;
        comment->maxSize *= 2;
    }

    comment->string[comment->currentSize] = character;
    ++comment->currentSize;
}

ErrorCode printComments(FILE* const inputFile, FILE* const outputFile)
{
    Comment* currentComment = NULL;
    State currentState = stateStart;

    while (!feof(inputFile))
    {
        const char character = getc(inputFile);
        changeState(&currentState, character);

        switch (currentState)
        {
        case stateFirstAsterisk:
            if ((currentComment = createComment()) == NULL)
            {
                return printErrorMessage(outOfMemory);
            }
            addCharacterToCommentString(currentComment, '/');
            addCharacterToCommentString(currentComment, '*');
            break;
        case stateCommentContent:
        case stateSecondAsterisk:
            if (addCharacterToCommentString(currentComment, character) == outOfMemory)
            {
                return printErrorMessage(outOfMemory);
            }
            break;
        case stateSecondSlash:
            if (addCharacterToCommentString(currentComment, character) == outOfMemory)
            {
                return printErrorMessage(outOfMemory);
            }
            currentComment->string[currentComment->currentSize] = '\0';
            fprintf(outputFile, "%s\n\n", currentComment->string);
            freeComment(currentComment);
            break;
        default:
            break;
        }
    }

    if (currentState != stateStart && currentState != stateSecondSlash)
    {
        freeComment(currentComment);
    }

    return ok;
}
