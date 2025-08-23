#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include <stdbool.h>
#include <string.h>
#include "repository.h"

#define SQLITE_BUFFER_SIZE 4096

typedef enum colum_pos
{
    id_pos = 0,
    name_pos,
    address_pos,
    age_pos,
} colum_pos;

REPOSITORY_BASE *sqlite_create_database(void);
bool sqlite_destroy_database(REPOSITORY_BASE *repository);

#endif /* SQLITE_DATABASE_H */