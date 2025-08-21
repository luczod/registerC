#include <stdbool.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"
#include "repository.h"

void use_case_person_add(REPOSITORY_BASE *repository)
{
    printf("\n---- Add a new person ----\n");

    PERSON_T person;
    person = person_create();

    repository->store(repository->object, &person);
}