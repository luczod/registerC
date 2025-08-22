#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "person.h"
#include "use_cases.h"
#include "repository.h"

void use_case_person_update(REPOSITORY_BASE *repository)
{
    printf("\n----- Update a person ----\n");

    int id = -1;
    int items = 0;
    PERSON_T *person_list;

    repository->recovery_list(repository->object, &person_list, &items);

    char *name_update = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_update, person_list[i].name, PERSON_NAME_LEN) == 0)
        {
            id = 1;
            break;
        }
    }

    if (id != -1)
    {

        memset(&person_list[id], 0, sizeof(PERSON_T));

        person_list[id] = person_create();
    }

    repository->store_list(repository->object, person_list, items);

    free(name_update);
    free(person_list);
}