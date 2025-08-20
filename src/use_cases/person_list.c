#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "database.h"
#include "use_cases.h"

void use_case_person_list(void)
{
    printf("\n----- List all people ----\n");
    FILE *file;

    if (db_is_database_exist())
    {
        file = fopen(DATABASE_FILE, "r");
    }
    else
    {
        printf("\nno people\n");
        return;
    }

    char c = fgetc(file);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(file);
    }
    fclose(file);
}