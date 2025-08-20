#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "use_cases.h"
#include "database.h"

void use_case_person_find(void)
{
    printf("\n------ Find a person -----\n");

    char *name_find = person_input_name();

    if (db_is_database_exist())
    {
        FILE *file = fopen(DATABASE_FILE, "r");

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char *buffer = calloc(1, size + 1);
        size_t len = fread(buffer, sizeof(char), size, file);

        if (ferror(file) != 0)
        {
            // code
        }
        else
        {
            buffer[len + 1] = '\0';
        }

        char *name_found = strstr(buffer, name_find);

        if (name_found != NULL)
        {
            char c;
            for (int i = 0;; i++)
            {
                c = name_found[i];
                if (c == '\n')
                    break;
                else
                    putc(c, stdout);
            }
            putc('\n', stdout);
        }
        free(name_find);
        free(buffer);
        fclose(file);
    }
}