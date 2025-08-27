#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "person_repository_file.h"

static bool person_repository_file_add(void *object, PERSON_T *person);
static bool person_repository_file_remove(void *object, PERSON_T *person);
static bool person_repository_file_update(void *object, PERSON_T *person);
static bool person_repository_file_find(void *object, PERSON_T *person);
static bool person_repository_file_getall(void *object, PERSON_T **person_list, unsigned int *amount);

static unsigned int person_repository_file_count_items(void);
static bool person_repository_file_is_database_exist(void);
static bool person_repository_file_parser(char *buffer, PERSON_T *person);

static bool person_repository_file_write_all(const PERSON_T *person_list, unsigned int items_amount);
static bool person_repository_file_read_all(PERSON_T **person_list, unsigned int *items_amount);

bool person_repository_file_init(PERSON_REPOSITORY_FILE_T *file)
{
    bool status = false;

    if (file != NULL)
    {
        memset(file, 0, sizeof(PERSON_REPOSITORY_FILE_T));

        file->base.object = file;
        file->base.add = person_repository_file_add;
        file->base.remove = person_repository_file_remove;
        file->base.update = person_repository_file_update;
        file->base.find = person_repository_file_find;
        file->base.getall = person_repository_file_getall;

        status = true;
    }

    return status;
}

bool person_repository_file_open(PERSON_REPOSITORY_FILE_T *file)
{
    bool status = false;
    if (file != NULL)
    {
        status = true;
    }
    return status;
}

bool person_repository_file_close(PERSON_REPOSITORY_FILE_T *file)
{
    bool status = false;
    if (file != NULL)
    {
        memset(file, 0, sizeof(PERSON_REPOSITORY_FILE_T));
        status = true;
    }
    return status;
}

PERSON_REPOSITORY_BASE_T person_repository_file_create(void)
{
    static PERSON_REPOSITORY_FILE_T file;

    person_repository_file_init(&file);
    person_repository_file_open(&file);

    return file.base;
}

static bool person_repository_file_add(void *object, PERSON_T *person)
{
    char format[DB_FORMAT_LEN + 1] = "";
    PERSON_REPOSITORY_FILE_T *file = (PERSON_REPOSITORY_FILE_T *)object;

    if (person_repository_file_is_database_exist() == false)
    {
        file->descriptor = (void *)fopen(DB_DATABASE_FILE, "w");
    }
    else
    {
        file->descriptor = fopen(DB_DATABASE_FILE, "a");
    }

    snprintf(format, DB_FORMAT_LEN, DB_DATABASE_FORMAT, person->name, person->address, person->age);
    fprintf((FILE *)file->descriptor, "%s", format);
    fclose((FILE *)file->descriptor);

    return true;
}

static bool person_repository_file_remove(void *object, PERSON_T *person)
{
    bool status = false;
    // PERSON_REPOSITORY_FILE_T *file = (PERSON_REPOSITORY_FILE_T *)object;

    PERSON_T *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all(&person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            if (person->id == person_list[i].id)
            {
                memset(&person_list[i], 0, sizeof(PERSON_T));
                person_repository_file_write_all(person_list, amount);
                free(person_list);
                status = true;
                break;
            }
        }
    }

    return status;
}

static bool person_repository_file_update(void *object, PERSON_T *person)
{
    bool status = false;
    // PERSON_REPOSITORY_FILE_T *file = (PERSON_REPOSITORY_FILE_T *)object;

    PERSON_T *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all(&person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            if (person->id == person_list[i].id)
            {
                memset(&person_list[i], 0, sizeof(PERSON_T));
                person_repository_file_write_all(person_list, amount);
                free(person_list);
                status = true;
                break;
            }
        }
    }

    return status;
}

static bool person_repository_file_find(void *object, PERSON_T *person)
{
    bool status = false;
    // PERSON_REPOSITORY_FILE_T *file = (PERSON_REPOSITORY_FILE_T *)object;

    PERSON_T *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_file_read_all(&person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            char *found = strstr(person_list[i].name, person->name);
            if (found != NULL)
            {
                memcpy(person, &person_list[i], sizeof(PERSON_T));
                status = true;
                break;
            }
        }

        free(person_list);
    }

    return status;
}

static bool person_repository_file_getall(void *object, PERSON_T **person_list, unsigned int *amount)
{
    bool status = false;
    // PERSON_REPOSITORY_FILE_T *file = (PERSON_REPOSITORY_FILE_T *)object;

    unsigned int _amount = 0;

    status = person_repository_file_read_all(person_list, &_amount);

    if (status == true)
        *amount = _amount;

    return status;
}

static bool person_repository_file_write_all(const PERSON_T *person_list, unsigned int items_amount)
{
    FILE *file;
    file = fopen(DB_DATABASE_FILE, "w");

    for (int i = 0; i < items_amount; i++)
    {
        if (person_list[i].name[0] == '\0' || person_list[i].address[0] == '\0')
            continue;

        fprintf(file, DB_DATABASE_FORMAT, person_list[i].name, person_list[i].address, person_list[i].age);
    }

    fclose(file);
    return true;
}

static bool person_repository_file_read_all(PERSON_T **person_list, unsigned int *items_amount)
{
    bool status = false;
    unsigned int items = person_repository_file_count_items();
    *items_amount = items;

    PERSON_T *_person_list = (PERSON_T *)malloc(sizeof(PERSON_T) * items);

    if (_person_list != NULL)
    {
        FILE *file = fopen(DB_DATABASE_FILE, "r");

        for (int i = 0; i < items; i++)
        {
            char buffer[DB_FORMAT_LEN] = "";
            fgets(buffer, DB_FORMAT_LEN, file);
            person_repository_file_parser(buffer, &_person_list[i]);
        }

        *person_list = _person_list;
        fclose(file);
        status = true;
    }

    return status;
}

static unsigned int person_repository_file_count_items(void)
{
    FILE *file;
    int items = 0;

    if (person_repository_file_is_database_exist())
        file = fopen(DB_DATABASE_FILE, "r");
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

static bool person_repository_file_is_database_exist(void)
{
    bool status = false;

    FILE *file = fopen(DB_DATABASE_FILE, "r");

    if (file != NULL)
    {
        fclose(file);
        status = true;
    }

    return status;
}

static bool person_repository_file_parser(char *buffer, PERSON_T *person)
{
    bool status = false;

    if (buffer == NULL || person == NULL)
    {
        char *temp = (char *)buffer;
        char *data = strtok(temp, ",");
        strncpy(person->name, data, PERSON_NAME_LEN);

        data = strtok(NULL, ",");
        strncpy(person->address, data, PERSON_ADDRESS_LEN);

        data = strtok(NULL, ",");
        person->age = atoi(data);

        status = true;
    }
    return status;
}
