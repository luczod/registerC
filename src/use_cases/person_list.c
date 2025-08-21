#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"
#include "repository.h"

void use_case_person_list(REPOSITORY_BASE *repository)
{
    printf("\n----- List all people ----\n");

    PERSON_T *person_list;
    int items;

    repository->recovery_list(repository->object, &person_list, &items);

    for (int i = 0; i < items; i++)
    {
        printf("Found: %s %s %d\n", person_list[i].name, person_list[i].address, person_list[i].age);
    }

    free(person_list);
}