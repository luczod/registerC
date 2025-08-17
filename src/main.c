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
int count_items(void);
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
    printf("\n---------- Menu ----------\n");
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
    printf("\n---- Add a new person ----\n");
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
    printf("\n---- Remove a person -----\n");

    int items = count_items();
    PERSON_T *people = (PERSON_T *)malloc(sizeof(PERSON_T) * items);

    if (people == NULL)
        return;

    FILE *file = fopen(DATABASE, "r");

    for (int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, file);
        char *data = strtok(buffer, ",");

        strncpy(people[i].name, data, PERSON_NAME_LEN);
        data = strtok(NULL, ",");

        strncpy(people[i].address, data, PERSON_ADDRESS_LEN);
        data = strtok(NULL, ",");

        people[i].age = atoi(data);
    }

    fclose(file);

    char name_delete[PERSON_NAME_LEN] = "";
    printf("Type a name to delete: ");
    fgets(name_delete, PERSON_NAME_LEN - 1, stdin);
    name_delete[strlen(name_delete) - 1] = 0;

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_delete, people[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&people[i], 0, sizeof(PERSON_T));
            break;
        }
    }

    file = fopen(DATABASE, "w");

    for (int i = 0; i < items; i++)
    {
        if (people[i].name[0] == '\0' || people[i].address[0] == '\0')
            continue;

        fprintf(file, "%s, %s, %d\n", people[i].name, people[i].address, people[i].age);
    }

    free(people);
    fclose(file);
}

void person_update(void)
{
    printf("\n----- Update a person ----\n");
    int id = -1;
    int items = count_items();

    PERSON_T *people = (PERSON_T *)malloc(sizeof(PERSON_T) * items);

    if (people == NULL)
        return;

    FILE *file = fopen(DATABASE, "r");

    for (int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, file);

        char *data = strtok(buffer, ",");
        strncpy(people[i].name, data, PERSON_NAME_LEN);

        data = strtok(NULL, ",");
        strncpy(people[i].address, data, PERSON_ADDRESS_LEN);

        data = strtok(NULL, ",");
        people[i].age = atoi(data);
    }

    fclose(file);
    char name_update[PERSON_NAME_LEN - 1] = "";
    printf("Type a name to update: ");
    fgets(name_update, PERSON_NAME_LEN - 1, stdin);
    name_update[strlen(name_update) - 1] = 0;

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_update, people[i].name, PERSON_NAME_LEN) == 0)
        {
            id = 1;
            break;
        }
    }

    if (id != -1)
    {

        memset(&people[id], 0, sizeof(PERSON_T));

        printf("Type a name: ");
        fgets(people[id].name, PERSON_NAME_LEN - 1, stdin);
        people[id].name[strlen(people[id].name) - 1] = 0;

        printf("Type a address: ");
        fgets(people[id].address, PERSON_ADDRESS_LEN - 1, stdin);
        people[id].address[strlen(people[id].address) - 1] = 0;

        printf("Type a age: ");
        scanf("%d", &people[id].age);
        getchar();
    }

    file = fopen(DATABASE, "w");

    for (int i = 0; i < items; i++)
    {
        if (people[i].name[0] == '\0' || people[i].address[0] == '\0')
            continue;

        fprintf(file, "%s, %s, %d\n", people[i].name, people[i].address, people[i].age);
    }

    free(people);
    fclose(file);
}

void person_list(void)
{
    printf("\n----- List all people ----\n");
    FILE *file;

    if (is_database_exist())
    {
        file = fopen(DATABASE, "r");
    }
    else
    {
        printf("\nno people\n");
        return;
    }

    char c = fgetc(file);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(file);
    }
    fclose(file);
}

void person_find(void)
{
    printf("Find a person\n");
}

int count_items(void)
{
    FILE *file;
    int items = 0;

    if (is_database_exist())
        file = fopen(DATABASE, "r");
    else
        return -1;

    char c = fgetc(file);
    while (c != EOF)
    {
        if (c == '\n')
            items++;
        c = fgetc(file);
    }
    fclose(file);

    return items;
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
