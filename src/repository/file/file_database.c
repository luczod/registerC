#include <stdlib.h>
#include <stdio.h>
#include "file_database.h"

static int file_count_items(void);
static bool file_is_database_exist(void);
static bool file_store(void *object, const PERSON_T *person);
static bool file_store_list(void *object, const PERSON_T *person_list, int items_amount);
static bool file_recovery_list(void *object, const PERSON_T **person_list, int *items_amount);
static void person_parser(const char *buffer, PERSON_T *person);

REPOSITORY_BASE *file_create_database(void)
{
    REPOSITORY_BASE *repository = (REPOSITORY_BASE *)malloc(sizeof(REPOSITORY_BASE));
    if (repository)
    {
        repository->object = NULL;
        repository->store = file_store;
        repository->store_list = file_store_list;
        repository->recovery_list = file_recovery_list;
    }
}

static bool file_store(void *object, const PERSON_T *person)
{
    FILE *file;

    if (db_is_database_exist() == false)
    {
        file = fopen(DATABASE_FILE, "w");
    }
    else
    {
        file = fopen(DATABASE_FILE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DATABASE_FORMAT, person->name, person->address, person->age);
    fprintf(file, "%s", format);
    fclose(file);

    return true;
}

static bool file_store_list(void *object, const PERSON_T *person_list, int items_amount)
{
    FILE *file;
    file = fopen(DATABASE_FILE, "w");

    for (int i = 0; i < items_amount; i++)
    {
        if (person_list[i].name[0] == '\0' || person_list[i].address[0] == '\0')
            continue;

        fprintf(file, DATABASE_FORMAT, person_list[i].name, person_list[i].address, person_list[i].age);
    }
    return true;
}

static bool file_recovery_list(void *object, const PERSON_T **person_list, int *items_amount)
{
    int items = db_count_items();
    *items_amount = items;

    PERSON_T *_person_list = (PERSON_T *)malloc(sizeof(PERSON_T) * items);

    if (_person_list == NULL)
        return;

    FILE *file = fopen(DATABASE_FILE, "r");

    for (int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, file);
        person_parser(buffer, &_person_list[i]);
    }

    *person_list = _person_list;
    fclose(file);

    return true;
}

static int file_count_items(void)
{
    FILE *file;
    int items = 0;

    if (file_is_database_exist())
        file = fopen(DATABASE_FILE, "r");
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

static bool file_is_database_exist(void)
{
    bool status = false;

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file != NULL)
    {
        fclose(file);
        status = true;
    }

    return status;
}

static void person_parser(const char *buffer, PERSON_T *person)
{
    char *temp = (char *)buffer;

    if (buffer == NULL || person == NULL)
        return;

    char *data = strtok(buffer, ",");
    strncpy(person->name, data, PERSON_NAME_LEN);

    data = strtok(NULL, ",");
    strncpy(person->address, data, PERSON_ADDRESS_LEN);

    data = strtok(NULL, ",");
    person->age = atoi(data);
}