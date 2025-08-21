#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "use_cases.h"
#include "database.h"
#include "repository.h"

void use_case_person_find(REPOSITORY_BASE *repository)
{
    printf("\n------ Find a person -----\n");

    bool status = false;
    int id = -1;
    char *name_find = person_input_name();

    PERSON_T *person_list;
    int items;

    repository->recovery_list(repository->object, &person_list, &items);

    for (int i = 0; i < items; i++)
    {
        char *found = strstr(person_list[i].name, name_find);
        if (found != NULL)
        {
            id = i;
            status = true;
            break;
        }
    }

    if (status)
        printf("Found: %s %s %d\n", person_list[id].name, person_list[id].address, person_list[id].age);
    else
        printf("Not Found\n");

    free(person_list);
    free(name_find);
}