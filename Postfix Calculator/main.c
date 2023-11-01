#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

#define LENGTH 51
#define OK 0
#define TESTS_FAILED 1
#define OUT_OF_MEMORY 2

void calcExpression(Stack** head, const char sign)
{
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    const int a = pop(head);
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    const int b = pop(head);
    if (*head == NULL)
    {
        push(head, 0);
        return;
    }

    switch (sign) 
    {
    case '+':
        push(head, a + b);
        break;
    case '-':
        push(head, b - a);
        break;
    case '*':
        push(head, a * b);
        break;
    case '/':
        push(head, b / a);
        break;
    }
}

int getResult(char* token)
{
    Stack* numbers = createStack();

    char const delimiter = ' ';
    char* context = NULL;
    size_t i = 0;
    while (token != NULL)
    {
        if (*token == '+' || *token == '-' || *token == '*' || *token == '/')
        {
            calcExpression(&numbers, *token);
        }
        else
        {
            const int x = atoi(token);
            push(&numbers, x);
        }
        token = strtok_s(NULL, &delimiter, &context);
    }

    ErrorCode errorCode = ok;
    const int result = top(numbers, &errorCode);
    freeStack(&numbers);
    return result;
}

bool test1() 
{
    char* const expression = "4 3 + 9 8 - / 5 *";
    char const delimiter = ' ';
    char* context = NULL;
    char* token = strtok_s(expression, &delimiter, &context);
    return getResult(token) == 35;
}

bool test2()
{
    char* const expression = "2 5 * 6 9 + *";
    char const delimiter = ' ';
    char* context = NULL;
    char* token = strtok_s(expression, &delimiter, &context);
    return getResult(token) == 150;
}

int main()
{
    if (!test1() || !test2()) 
    {
        printf("~ Tests have failed");
        return TESTS_FAILED;
    }
    char* const expression = (char*)malloc(sizeof(char) * LENGTH);
    if (expression == NULL) 
    {
        printf("~ Memory allocation has failed");
        return OUT_OF_MEMORY;
    }
    char const delimiter = ' ';
    char* context = NULL;
    printf("Enter an expression (up to 50 symbols): ");
    fgets(expression, LENGTH, stdin);
    char *token = strtok_s(expression, &delimiter, &context);
    const int expressionResult = getResult(token);

    printf("The result is %d", expressionResult);

    return OK;
}
