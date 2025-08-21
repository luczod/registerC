#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdbool.h>
#include "person.h"

typedef struct
{
    void *object;
    bool (*store)(void *object, const PERSON_T *person);
    bool (*store_list)(void *object, const PERSON_T *person_list, int items_amount);
    bool (*recovery_list)(void *object, const PERSON_T **person_list, int *items_amount);
} REPOSITORY_BASE;

bool person_store(REPOSITORY_BASE *repository, const PERSON_T *person);
bool person_store_list(REPOSITORY_BASE *repository, const PERSON_T *person_list, int items_amount);
bool person_recovery_list(REPOSITORY_BASE *repository, const PERSON_T **person_list, int *item_amount);

#endif /* REPOSITORY_H */