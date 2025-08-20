#include <stdio.h>
#include <stdbool.h>
#include "database.h"

int db_count_items(void)
{
    FILE *file;
    int items = 0;

    if (db_is_database_exist())
        file = fopen(DATABASE_FILE, "r");
    else
        return -1;

    char c = fgetc(file);
    while (c != EOF)
    {
        if (c == '\n')
            items++;
        c = fgetc(file);
    }
    fclose(file);

    return items;
}

bool db_is_database_exist(void)
{
    bool status = false;

    FILE *file = fopen(DATABASE_FILE, "r");

    if (file != NULL)
    {
        fclose(file);
        status = true;
    }

    return status;
}