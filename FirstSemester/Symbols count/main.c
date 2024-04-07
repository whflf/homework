#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define FILE_OPEN_ERROR -1
#define OK 0
#define OUT_OF_MEMORY 1
#define TESTS_FAILED 2


int charCount(int* const array, char* const filename)
{
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0)
    {
        return FILE_OPEN_ERROR;
    }

    while (!feof(file))
    {
        const int character = fgetc(file);
        ++array[character];
    }

    fclose(file);
}

bool test1() 
{
    int* const characters = (int*)calloc(256, sizeof(int) * 256);
    if (characters == NULL) 
    {
        return 0;
    }
    if (charCount(characters, "test1.txt") != FILE_OPEN_ERROR) 
    {
        return characters[10] == 13;
    }

    free(characters);
    return 0;
}

bool test2()
{
    int* const characters = (int*)calloc(256, sizeof(int) * 256);
    if (characters == NULL)
    {
        return 0;
    }
    if (charCount(characters, "test2.txt") != FILE_OPEN_ERROR)
    {
        return characters[32] == 15 && characters[78] == 1 && characters[10] == 0 && characters[111] == 8;
    }

    free(characters);
    return 0;
}

int main()
{
    if (!test1() || !test2()) {
        printf("~ Tests have failed");
        return TESTS_FAILED;
    }

    int* const characters = (int*)calloc(256, sizeof(int) * 256);
    if (characters == NULL)
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }

    if (charCount(characters, "file.txt") != FILE_OPEN_ERROR) {
        for (size_t i = 0; i < 256; ++i) {
            if (characters[i] == 0)
            {
                continue;
            }
            printf("%c - %d\n", (char)i, characters[i]);
        }
    }

    free(characters);
    return OK;
}
