#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"
#include "errors.h"

void deleteOddElements(List** head)
{
    size_t listSize = size(*head);
    for (size_t i = 1; i < listSize; i += 2)
    {
        delete(head, i);
    }
    renumber(head);
}

int main(void)
{
    List* list = NULL;
    append(&list, 1);
    append(&list, 2);
    append(&list, 3);
    append(&list, 4);
    append(&list, 5);
    append(&list, 6);
    printList(list);
    deleteOddElements(&list);
    printList(list);
    deleteOddElements(&list);
    printList(list);
    deleteOddElements(&list);
    printList(list);
    deleteOddElements(&list);
    printList(list);
    deleteList(&list);
}
