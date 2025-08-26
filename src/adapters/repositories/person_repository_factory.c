#include "person_repository_factory.h"
#include "person_repository_file.h"
#include "person_repository_sqlite.h"

PERSON_REPOSITORY_BASE_T person_repository_create(PERSON_REPOSITORY_TYPE type)
{
    PERSON_REPOSITORY_BASE_T base;

    if (type == PERSON_REPOSITORY_TYPE_FILE)
    {
        base = person_repository_create(type);
    }

    if (type == PERSON_REPOSITORY_TYPE_SQLITE)
    {
        base = person_repository_create(type);
    }

    return base;
}