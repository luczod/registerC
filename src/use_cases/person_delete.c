#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"

void use_case_person_delete(void)
{
    printf("\n---- Remove a person -----\n");

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

    char *name_delete = person_input_name();

    for (int i = 0; i < items; i++)
    {
        if (strncmp(name_delete, people[i].name, PERSON_NAME_LEN) == 0)
        {
            memset(&people[i], 0, sizeof(PERSON_T));
            break;
        }
    }

    file = fopen(DATABASE_FILE, "w");

    for (int i = 0; i < items; i++)
    {
        if (people[i].name[0] == '\0' || people[i].address[0] == '\0')
            continue;

        fprintf(file, DATABASE_ROW, people[i].name, people[i].address, people[i].age);
    }

    free(name_delete);
    free(people);
    fclose(file);
}