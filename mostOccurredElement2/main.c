#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/qsort.h"
#include "include/errors.h"

#define INPUT_FILE_NAME "input.txt"
#define INPUT_FILE_NAME_TEST_CORRECT "staticFiles/testCorrectFile.txt"
#define INPUT_FILE_NAME_TEST_MIXED "staticFiles/testMixedFile.txt"
#define INPUT_FILE_NAME_TEST_BAD "staticFiles/testBadFile.txt"

int getMostOccurredElement(int* const numbers, const size_t size)
{
    quicksort(numbers, 0, size - 1);

    int mostOccurredElement = numbers[0];
    int currentElement = numbers[0];
    int currentCount = 1;
    int maxCount = 1;

    for (size_t i = 1; i < size; ++i)
    {
        if (numbers[i] == currentElement)
        {
            ++currentCount;
            if (currentCount > maxCount)
            {
                maxCount = currentCount;
                mostOccurredElement = currentElement;
            }
        }
        else
        {
            currentElement = numbers[i];
            currentCount = 1;
        }
    }

    return mostOccurredElement;
}

int scanFileInts(const char* const filename, int** intArray, size_t* intArraySize)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("scanFileInts: File %s can not be opened.\n", filename);
        return fileError;
    }

    fseek(file, 0, SEEK_END);

    const long fileSize = ftell(file);
    if (fileSize == -1L)
    {
        printf("scanFileInts: ftell() call failed.\n");
        fclose(file);
        return fileError;
    }

    fseek(file, 0, SEEK_SET);

    *intArray = (int*)calloc(fileSize, sizeof(int));
    if (*intArray == NULL)
    {
        printf("scanFileInts: Couldn't allocate memory for intArray.\n");
        return outOfMemory;
    }

    for (*intArraySize = 0; fscanf(file, "%d", &(*intArray)[*intArraySize]) == 1; ++(*intArraySize)); 

    fclose(file);
    return ok;
}

int getMostOccurredElementFromFile(const char* const filename, int* mostOccurredElement)
{
    int* numbers = NULL;
    size_t numberSize = 0;

    int error;
    if ((error = scanFileInts(filename, &numbers, &numberSize)) != ok)
    {
        return error;
    }

    if (numberSize == 0)
    {
        free(numbers);
        return emptyArray;
    }

    *mostOccurredElement = getMostOccurredElement(numbers, numberSize);

    free(numbers);
    return ok;
}

bool testCorrectFile()
{
    int mostOccurredElementValue;
    int error = getMostOccurredElementFromFile(INPUT_FILE_NAME_TEST_CORRECT, &mostOccurredElementValue);
    return error == ok && mostOccurredElementValue == 42;
}

bool testMixedFile()
{
    int mostOccurredElementValue;
    int error = getMostOccurredElementFromFile(INPUT_FILE_NAME_TEST_MIXED, &mostOccurredElementValue);
    return error == ok && mostOccurredElementValue == -3;
}

bool testBadFile()
{
    int error = getMostOccurredElementFromFile(INPUT_FILE_NAME_TEST_BAD, NULL);
    return error == emptyArray;
}

int main(void)
{
    if (!testCorrectFile() || !testMixedFile() || !testBadFile())
    {
        printf("Tests failed.\n");
        return testsFailed;
    }

    int error, mostOccurredElementValue;

    if ((error = getMostOccurredElementFromFile(INPUT_FILE_NAME, &mostOccurredElementValue)) != ok)
    {
        if (error == emptyArray)
        {
            printf("Got nothing (array size = 0).\n");
        }
        return error;
    }

    printf(
        "Most occurred number in \"%s\" is %d.\n",
        INPUT_FILE_NAME,
        mostOccurredElementValue
    );

    return ok;
}
