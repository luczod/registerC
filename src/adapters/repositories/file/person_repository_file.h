#ifndef PERSON_REPOSITORY_FILE_H
#define PERSON_REPOSITORY_FILE_H

#include "person_repository_base.h"

#define DB_DATABASE_FORMAT "%s %s %d\n"
#define DB_DATABASE_FILE "database.txt"
#define DB_FORMAT_LEN (PERSON_NAME_LEN + PERSON_ADDRESS_LEN + 40)

typedef struct PERSON_REPOSITORY_FILE_T
{
    PERSON_REPOSITORY_BASE_T base;
    void *destroy;
    void *descriptor;
} PERSON_REPOSITORY_FILE_T;

bool person_repository_file_init(PERSON_REPOSITORY_FILE_T *file);
bool person_repository_file_open(PERSON_REPOSITORY_FILE_T *file);
bool person_repository_file_close(PERSON_REPOSITORY_FILE_T *file);

PERSON_REPOSITORY_FILE_T person_repository_file_create(void);

#endif /* PERSON_REPOSITORY_FILE_H */