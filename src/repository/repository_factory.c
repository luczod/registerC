#include <stdlib.h>
#include <string.h>
#include "repository_factory.h"
#include "file_database.h"
#include "sqlite_database.h"

typedef struct DATABASE_T
{
    const char *name;
    REPOSITORY_BASE *(*database_create)(void);
    bool (*database_destroy)(REPOSITORY_BASE *repository);
} DATABASE_T;

DATABASE_T databases[] = {
    {
        .name = "file",
        .database_create = file_create_database,
        .database_destroy = file_destroy_database,
    },
    {
        .name = "sqlite",
        .database_create = sqlite_create_database,
        .database_destroy = sqlite_destroy_database,
    },
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

bool repository_destroy(const char *type, REPOSITORY_BASE *repository)
{
    bool status = false;
    if (repository != NULL)
    {
        for (int i = 0; i < database_amount; i++)
        {
            if (strncmp(databases[i].name, type, strlen(databases[i].name)) == 0)
            {
                status = databases[i].database_destroy(repository);
                break;
            }
        }
    }

    return status;
}