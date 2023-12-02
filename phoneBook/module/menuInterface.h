#pragma once

#include "phoneBook.h"

#define ALLOC_SIZE 16

#define MENU_TEXT "\
Enter an operation code to continue:\n\
  0 - Exit\n\
  1 - Add an entry\n\
  2 - Print existing entries\n\
  3 - Find phone number by name\n\
  4 - Find name by phone number\n\
  5 - Save everything to database file\n\
> "
#define OUT_OF_MEMORY_TEXT "Couldn't allocate memory.\n"

void programLoop(Book* const book);
