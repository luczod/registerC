#ifndef MENU_REGSITER_H
#define MENU_REGSITER_H

#include <stdbool.h>
#include "repository.h"

#define MENU_TEXT_ADD_PERSON "1. Add a new person"
#define MENU_TEXT_REMOVE_PERSON "2. Remove a person"
#define MENU_TEXT_UPDATE_PERSON "3. Update a person"
#define MENU_TEXT_LIST_PERSON "4. List all people"
#define MENU_TEXT_FIND_PERSON "5. Find a person"
#define MENU_TEXT_EXIT "6. exit program"
#define MENU_TEXT_CURSOR "> "

typedef enum
{
    menu_option_add = 1,
    menu_option_remove,
    menu_option_update,
    menu_option_list,
    menu_option_find,
    menu_option_quit

} MENU_OPTION_T;

// pointer to function
typedef void (*menu_option_base)(REPOSITORY_BASE *repository);

typedef struct MENU_COMMANDS_T
{
    MENU_OPTION_T option;
    menu_option_base command;
} MENU_COMMANDS_T;

void print_menu(void);

bool option_select(int option, REPOSITORY_BASE *repository);

#endif