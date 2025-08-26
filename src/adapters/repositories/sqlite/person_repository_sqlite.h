#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include <stdbool.h>
#include <string.h>
#include "person_repository_base.h"

#define SQLITE_BUFFER_SIZE 4096

typedef struct PERSON_REPOSITORY_SQLITE_T
{
    PERSON_REPOSITORY_BASE_T base;
    const char *database_name;
    void *connection;
} PERSON_REPOSITORY_SQLITE_T;

typedef enum colum_pos
{
    id_pos = 0,
    name_pos,
    address_pos,
    age_pos,
} colum_pos;

bool person_repository_sqlite_init(PERSON_REPOSITORY_SQLITE_T *sqlite);
bool person_repository_sqlite_open(PERSON_REPOSITORY_SQLITE_T *sqlite);
bool person_repository_sqlite_close(PERSON_REPOSITORY_SQLITE_T *sqlite);

PERSON_REPOSITORY_BASE_T person_repository_sqlite_create(void);

#endif /* SQLITE_DATABASE_H */