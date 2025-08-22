#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdbool.h>
#include "person.h"

typedef enum
{
    repo_insert,
    repo_update,
    repo_delete
} REPO_ACTION_T;

typedef struct STORE_ACTION_T
{
    REPO_ACTION_T action;
    PERSON_T *person;
    int id;
    int amount;
} STORE_ACTION_T;

typedef struct REPOSITORY_BASE
{
    void *object;
    bool (*store)(void *object, STORE_ACTION_T *action);
    bool (*store_list)(void *object, const PERSON_T *person_list, int items_amount);
    bool (*recovery_list)(void *object, PERSON_T **person_list, int *items_amount);
} REPOSITORY_BASE;

bool person_store(REPOSITORY_BASE *repository, STORE_ACTION_T *action);
bool person_store_list(REPOSITORY_BASE *repository, const PERSON_T *person_list, int items_amount);
bool person_recovery_list(REPOSITORY_BASE *repository, PERSON_T **person_list, int *item_amount);

#endif /* REPOSITORY_H */