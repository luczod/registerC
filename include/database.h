#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdbool.h>

#define DATABASE_FILE "database.txt"
#define DATABASE_ROW "%s, %s, %d\n"

int db_count_items(void);
bool db_is_database_exist(void);

#endif