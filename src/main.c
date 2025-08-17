#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <person.h>

#define DATABASE "database.txt"
#define TEXT_ADD_PERSON "1. Add a new person"
#define TEXT_REMOVE_PERSON "2. Remove a person"
#define TEXT_UPDATE_PERSON "3. Update a person"
#define TEXT_LIST_PERSON "4. List all people"
#define TEXT_FIND_PERSON "5. Find a person"
#define TEXT_EXIT "6. exit program"
#define TEXT_CURSOR "> "

void print_menu(void);
bool option_select(int option);

void person_add(void);
void person_delete(void);
void person_update(void);
void person_list(void);
void person_find(void);

bool is_database_exist(void);

int main(void)
{
    int option;

    do
    {
        print_menu();
        scanf("%d", &option);
        getchar();
    } while (option_select(option));

    return EXIT_SUCCESS;
}

void print_menu(void)
{
    printf("%s\n", TEXT_ADD_PERSON);
    printf("%s\n", TEXT_REMOVE_PERSON);
    printf("%s\n", TEXT_UPDATE_PERSON);
    printf("%s\n", TEXT_LIST_PERSON);
    printf("%s\n", TEXT_FIND_PERSON);
    printf("%s\n", TEXT_EXIT);
    printf("%s ", TEXT_CURSOR);
}

bool option_select(int option)
{
    bool status = true;
    switch (option)
    {
    case 1:
        person_add();
        break;
    case 2:
        person_delete();
        break;
    case 3:
        person_update();
        break;
    case 4:
        person_list();
        break;
    case 5:
        person_find();
        break;
    case 6:
        printf("Exit program ----------\n");
        status = false;
        break;

    default:
        printf("no option selected");
        break;
    }
    return status;
}

void person_add(void)
{
    printf("---------- Add a new person ----------\n");
    PERSON_T person;
    FILE *file;

    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name) - 1] = 0;

    printf("Type a address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address) - 1] = 0;

    printf("Type a age: ");
    scanf("%d", &person.age);
    getchar();

    if (is_database_exist() == false)
    {
        file = fopen(DATABASE, "w");
    }
    else
    {
        file = fopen(DATABASE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, "%s, %s, %d\n", person.name, person.address, person.age);
    fprintf(file, "%s", format);
    fclose(file);
}

void person_delete(void)
{
    printf("Remove a person\n");
}

void person_update(void)
{
    printf("Update a person\n");
}

void person_list(void)
{
    printf("List all people\n");
}

void person_find(void)
{
    printf("Find a person\n");
}

bool is_database_exist(void)
{
    bool status = false;

    FILE *file = fopen(DATABASE, "r");

    if (file != NULL)
    {
        fclose(file);
        status = true;
    }

    return status;
}
