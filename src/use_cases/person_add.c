#include <stdbool.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"

void use_case_person_add(void)
{
    printf("\n---- Add a new person ----\n");

    PERSON_T person;
    FILE *file;

    person = person_create();

    if (db_is_database_exist() == false)
    {
        file = fopen(DATABASE_FILE, "w");
    }
    else
    {
        file = fopen(DATABASE_FILE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, DATABASE_ROW, person.name, person.address, person.age);
    fprintf(file, "%s", format);
    fclose(file);
}