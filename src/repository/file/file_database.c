#include <stdlib.h>
#include "file_database.h"

static bool file_store(void *object, const PERSON_T *person)
{
    return true;
}
static bool file_store_list(void *object, const PERSON_T *person_list, int items_amount)
{
    return true;
}
static bool file_recovery_list(void *object, const PERSON_T **person_list, int *items_amount)
{
    return true;
}

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