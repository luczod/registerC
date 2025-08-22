#include <stdlib.h>
#include <string.h>
#include "repository_factory.h"
#include "file_database.h"

const char *types[] = {"file"};

REPOSITORY_BASE *repopository_create(const char *type)
{
    REPOSITORY_BASE *repository = NULL;

    if (strncmp(types[0], type, strlen(types[0])) == 0)
    {
        repository = file_create_database();
    }

    return repository;
}