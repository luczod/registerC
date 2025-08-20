#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"

void use_case_person_update(void)
{
    printf("\n----- Update a person ----\n");
    int id = -1;
    int items = db_count_items();

    PERSON_T *people = (PERSON_T *)malloc(sizeof(PERSON_T) * items);

    if (people == NULL)
        return;

    FILE *file = fopen(DATABASE_FILE, "r");

    for (int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, file);

        person_parser(buffer, &people[i]);
    }

    fclose(file);
    char *name_update = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_update, people[i].name, PERSON_NAME_LEN) == 0)
        {
            id = 1;
            break;
        }
    }

    if (id != -1)
    {

        memset(&people[id], 0, sizeof(PERSON_T));

        people[id] = person_create();
    }

    file = fopen(DATABASE_FILE, "w");

    for (int i = 0; i < items; i++)
    {
        if (people[i].name[0] == '\0' || people[i].address[0] == '\0')
            continue;

        fprintf(file, DATABASE_ROW, people[i].name, people[i].address, people[i].age);
    }

    free(name_update);
    free(people);
    fclose(file);
}