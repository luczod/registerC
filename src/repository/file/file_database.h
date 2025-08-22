#ifndef FILE_DATABASE_H
#define FILE_DATABASE_H

#include <stdbool.h>
#include <string.h>
#include "repository.h"

#define DATABASE_FORMAT "%s, %s, %d\n"
#define DATABASE_FILE "database.txt"

REPOSITORY_BASE *file_create_database(void);

#endif /* FILE_DATABASE_H */