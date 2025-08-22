#include "repository.h"
/* interface */

bool person_store(REPOSITORY_BASE *repository, const PERSON_T *person)
{
    return repository->store(repository->object, person);
}

bool person_store_list(REPOSITORY_BASE *repository, const PERSON_T *person_list, int items_amount)
{
    return repository->store_list(repository->object, person_list, items_amount);
}

bool person_recovery_list(REPOSITORY_BASE *repository, PERSON_T **person_list, int *item_amount)
{
    return repository->recovery_list(repository->object, person_list, item_amount);
}
