#include <stdlib.h>
#include <string.h>
#include "repository_factory.h"
#include "file_database.h"
#include "sqlite_database.h"

typedef struct DATABASE_T
{
    const char *name;
    REPOSITORY_BASE *(*database_create)(void);
} DATABASE_T;

DATABASE_T databases[] = {
    {.name = "file", .database_create = file_create_database},
    {.name = "sqlite", .database_create = sqlite_create_database},
};

const unsigned int database_amount = sizeof(databases) / sizeof(databases[0]);

REPOSITORY_BASE *repopository_create(const char *type)
{
    REPOSITORY_BASE *repository = NULL;

    for (int i = 0; i < database_amount; i++)
    {
        if (strncmp(databases[i].name, type, strlen(databases[i].name)) == 0)
        {
            repository = databases[i].database_create();
            break;
        }
    }

    return repository;
}