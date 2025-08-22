#include <stdbool.h>
#include <stdio.h>
#include "person.h"
#include "use_cases.h"
#include "repository.h"

void use_case_person_add(REPOSITORY_BASE *repository)
{
    printf("\n---- Add a new person ----\n");

    PERSON_T person;
    STORE_ACTION_T store;
    person = person_create();

    store.action = repo_insert;
    store.id = -1;
    store.amount = 1;
    store.person = &person;

    repository->store(repository->object, &store);
}