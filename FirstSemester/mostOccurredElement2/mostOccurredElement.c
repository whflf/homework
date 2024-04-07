#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "include/errors.h"
#include "include/qsort.h"
#include "mostOccurredElement.h"

static int getMostOccurredElement(int* const numbers, const size_t size)
{
    quicksort(numbers, 0, (int)(size - 1));

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

static ErrorCode scanFileInts(const char* const filename, int** const intArray, size_t* const intArraySize)
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

    int temp;
    size_t tempCounter;
    for (tempCounter = 0; fscanf(file, "%d", &temp) == 1; ++tempCounter);

    if (tempCounter == 0)
    {
        return emptyArray;
    }

    *intArray = (int*)calloc(tempCounter, sizeof(int));
    if (*intArray == NULL)
    {
        printf("scanFileInts: Couldn't allocate memory (%zu bytes) for intArray.\n", tempCounter * sizeof(int));
        return outOfMemory;
    }

    fseek(file, 0, SEEK_SET);
    for (*intArraySize = 0; fscanf(file, "%d", &(*intArray)[*intArraySize]) == 1; ++*intArraySize);

    fclose(file);
    return ok;
}

int getMostOccurredElementFromFile(const char* const filename, int* const mostOccurredElement)
{
    int* numbers = NULL;
    size_t numberSize = 0;

    ErrorCode error;
    if ((error = scanFileInts(filename, &numbers, &numberSize)) != ok)
    {
        return error;
    }

    *mostOccurredElement = getMostOccurredElement(numbers, numberSize);

    free(numbers);
    return ok;
}
