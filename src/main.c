#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <person.h>

#define DATABASE "database.txt"
#define DATABASE_ROW "%s, %s, %d\n"

#define TEXT_ADD_PERSON "1. Add a new person"
#define TEXT_REMOVE_PERSON "2. Remove a person"
#define TEXT_UPDATE_PERSON "3. Update a person"
#define TEXT_LIST_PERSON "4. List all people"
#define TEXT_FIND_PERSON "5. Find a person"
#define TEXT_EXIT "6. exit program"
#define TEXT_CURSOR "> "

typedef enum
{
    option_add = 1,
    option_remove,
    option_update,
    option_list,
    option_find,
    option_quit

} OPTION_T;

// pointer to function
typedef void (*option_base)(void);

typedef struct
{
    OPTION_T option;
    option_base command;
} COMMANDS_T;

void print_menu(void);
bool option_select(int option);

void person_add(void);
void person_delete(void);
void person_update(void);
void person_list(void);
void person_find(void);
void person_quit(void);

int count_items(void);
bool is_database_exist(void);

PERSON_T person_create(void);
char *person_input_name(void);
void person_parser(char *buffer, PERSON_T *people);

int main(void)
{
    int option;

    while (true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option);
    }

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

    COMMANDS_T options[] = {
        {.option = option_add, .command = person_add},
        {.option = option_remove, .command = person_delete},
        {.option = option_update, .command = person_update},
        {.option = option_list, .command = person_list},
        {.option = option_find, .command = person_find},
        {.option = option_quit, .command = person_quit},
    };

    int list_size = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < list_size; i++)
    {
        if (option == options[i].option)
        {
            options[i].command();
            break;
        }
    }

    return status;
}

void person_add(void)
{
    printf("\n---- Add a new person ----\n");

    PERSON_T person;
    FILE *file;

    person = person_create();

    if (is_database_exist() == false)
    {
        file = fopen(DATABASE, "w");
    }
    else
    {
        file = fopen(DATABASE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DATABASE_ROW, person.name, person.address, person.age);
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
        person_parser(buffer, &people[i]);
    }

    fclose(file);

    char *name_delete = person_input_name();

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

        fprintf(file, DATABASE_ROW, people[i].name, people[i].address, people[i].age);
    }

    free(name_delete);
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

        person_parser(buffer, &people[i]);
    }

    fclose(file);
    char *name_update = person_input_name();

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

        people[id] = person_create();
    }

    file = fopen(DATABASE, "w");

    for (int i = 0; i < items; i++)
    {
        if (people[i].name[0] == '\0' || people[i].address[0] == '\0')
            continue;

        fprintf(file, DATABASE_ROW, people[i].name, people[i].address, people[i].age);
    }

    free(name_update);
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
    printf("\n------ Find a person -----\n");

    char *name_find = person_input_name();

    if (is_database_exist())
    {
        FILE *file = fopen(DATABASE, "r");

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char *buffer = calloc(1, size + 1);
        size_t len = fread(buffer, sizeof(char), size, file);

        if (ferror(file) != 0)
        {
            // code
        }
        else
        {
            buffer[len + 1] = '\0';
        }

        char *name_found = strstr(buffer, name_find);

        if (name_found != NULL)
        {
            char c;
            for (int i = 0;; i++)
            {
                c = name_found[i];
                if (c == '\n')
                    break;
                else
                    putc(c, stdout);
            }
            putc('\n', stdout);
        }
        free(name_find);
        free(buffer);
        fclose(file);
    }
}

void person_quit(void)
{
    printf("Exit program ----------\n");
    exit(0);
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

PERSON_T person_create(void)
{
    PERSON_T person;

    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name) - 1] = 0;

    printf("Type a address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address) - 1] = 0;

    printf("Type a age: ");
    scanf("%d", &person.age);
    getchar();

    return person;
}

char *person_input_name(void)
{
    char *name = calloc(1, PERSON_NAME_LEN + 1);
    printf("Type a name to find: ");
    fgets(name, PERSON_NAME_LEN - 1, stdin);
    // remove the trailing newline by overwriting the last character with '\0'.
    name[strlen(name) - 1] = 0;

    return name;
}

void person_parser(char *buffer, PERSON_T *person)
{
    if (buffer == NULL || person == NULL)
        return;

    char *data = strtok(buffer, ",");
    strncpy(person->name, data, PERSON_NAME_LEN);

    data = strtok(NULL, ",");
    strncpy(person->address, data, PERSON_ADDRESS_LEN);

    data = strtok(NULL, ",");
    person->age = atoi(data);
}
