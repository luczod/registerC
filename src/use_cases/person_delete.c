#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "person.h"
#include "use_cases.h"
#include "repository.h"

void use_case_person_delete(REPOSITORY_BASE *repository)
{
    printf("\n---- Remove a person -----\n");

    int items = 0;
    PERSON_T *person_list;
    STORE_ACTION_T store;

    repository->recovery_list(repository->object, &person_list, &items);

    char *name_delete = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_delete, person_list[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&person_list[i], 0, sizeof(PERSON_T));

            store.id = i;
            store.action = repo_delete;
            store.amount = items;
            store.person = person_list;

            repository->store(repository->object, &store);

            break;
        }
    }

    free(name_delete);
    free(person_list);
}