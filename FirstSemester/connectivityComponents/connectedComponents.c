#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "connectedComponents.h"

static void depthFirstSearch(const int source, const int vertex, const int numberOfVertices, const int* const* const incidenceMatrix, int*** components, bool** visitedFlags)
{
    *visitedFlags[vertex] = true;
    for (size_t i = 0; i < numberOfVertices; ++i)
    {
        if (*components[source][i] == 0)
        {
            *components[source][i] = vertex + 1;
            break;
        }
    }

    for (size_t nextVertex = 0; nextVertex < numberOfVertices; ++nextVertex) 
    {
        if (incidenceMatrix[vertex][nextVertex] == 1 && !visitedFlags[nextVertex]) 
        {
            depthFirstSearch(source, nextVertex, numberOfVertices, incidenceMatrix, components, visitedFlags);
        }
    }
}

static int** findConnectedComponents(const size_t numberOfVertices, const int* const* const incidenceMatrix)
{
    bool* visitedFlags = (bool*)calloc(numberOfVertices, sizeof(bool));
    if (visitedFlags == NULL)
    {
        return NULL;
    }

    int** connectedComponents = (int**)calloc(numberOfVertices, sizeof(int*));
    if (connectedComponents == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < numberOfVertices; ++i)
    {
        connectedComponents[i] = (int*)calloc(numberOfVertices, sizeof(int));
        if (connectedComponents[i] == NULL)
        {
            return NULL;
        }
    }

    for (size_t vertex = 0; vertex < numberOfVertices; ++vertex)
    {
        if (!visitedFlags[vertex])
        {
            depthFirstSearch(vertex, vertex, numberOfVertices, incidenceMatrix, &connectedComponents, &visitedFlags);
        }
    }

    return connectedComponents;
}

void printComponents(const int* const* const incidenceMatrix, const size_t numberOfVertices)
{
    int** componentsArray = findConnectedComponents(numberOfVertices, incidenceMatrix);
    if (componentsArray == NULL)
    {
        printf("~ Couldn't allocate memory.\n");
        return;
    }

    printf("Connected components:\n");
    for (size_t i = 0; i < numberOfVertices; ++i)
    {
        for (size_t j = 0; i < numberOfVertices; ++i)
        {
            if (componentsArray[i][j] == 0)
            {
                break;
            }
            printf("%d, ", componentsArray[i][j]);
        }
        printf("\n");
    }
}
