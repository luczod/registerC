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
    STORE_ACTION_T store;

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
        PERSON_T person_tmp;
        store.id = id;
        store.action = repo_update;
        store.amount = items;
        store.person = person_list;

        person_tmp = person_create();
        strncpy(person_list[id].name, person_tmp.name, PERSON_NAME_LEN);
        strncpy(person_list[id].address, person_tmp.address, PERSON_ADDRESS_LEN);
        person_list[id].age = person_tmp.age;

        repository->store(repository->object, &store);
    }

    free(name_update);
    free(person_list);
}