#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

struct Matrix
{
    size_t rowCount;
    size_t columnCount;
    int** array;
};

static Matrix* createMatrix(const size_t m, const size_t n)
{
    Matrix* const newMatrix = (Matrix*)malloc(sizeof(Matrix));
    if (newMatrix == NULL)
    {
        return NULL;
    }

    newMatrix->rowCount = m;
    newMatrix->columnCount = n;

    newMatrix->array = (int**)malloc(m * sizeof(int*));
    if (newMatrix->array == NULL)
    {
        free(newMatrix);
        return NULL;
    }

    for (size_t i = 0; i < m; ++i)
    {
        newMatrix->array[i] = (int*)malloc(n * sizeof(int));
        if (newMatrix->array[i] == NULL)
        {
            free(newMatrix->array);
            free(newMatrix);
            return NULL;
        }
    }
}

Matrix* getMatrix(void)
{
    size_t m = 0;
    size_t n = 0;

    printf("> Enter rows number (m): ");
    scanf("%llu", &m);

    printf("> Enter columns number (m): ");
    scanf("%llu", &n);

    if (m == 0 || n == 0)
    {
        printf("Bad input. Please enter a valid size.\n");
        return NULL;
    }

    Matrix* matrix = createMatrix(m, n);
    if (matrix == NULL)
    {
        printf("Couldn't allocate memory.\n");
    }

    printf("> Enter the numbers:\n");
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            const int fieldsFilled = scanf("%d", &matrix->array[i][j]);
            if (fieldsFilled == 0)
            {
                printf("Wrong input. Please enter valid integers.\n");
                return NULL;
            }
        }
    }

    return matrix;
}
