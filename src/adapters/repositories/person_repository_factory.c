#include "person_repository_factory.h"
#include "person_repository_file.h"
#include "person_repository_sqlite.h"
#include "configuration.h"

PERSON_REPOSITORY_BASE_T person_repository_create(const char *type)
{
    PERSON_REPOSITORY_BASE_T base;

    if (strcmp(type, CONFIGURATION_REPOSITORY_TYPE_FILE) == 0)
    {
        base = person_repository_file_create();
    }

    if (strcmp(type, CONFIGURATION_REPOSITORY_TYPE_SQLITE) == 0)
    {
        base = person_repository_sqlite_create();
    }

    return base;
}