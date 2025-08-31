#ifndef PERSON_REPOSITORY_FACTORY_H
#define PERSON_REPOSITORY_FACTORY_H

#include "person_repository_base.h"

// typedef enum PERSON_REPOSITORY_TYPE
// {
//     PERSON_REPOSITORY_TYPE_FILE = 1,
//     PERSON_REPOSITORY_TYPE_SQLITE,
// } PERSON_REPOSITORY_TYPE;

PERSON_REPOSITORY_BASE_T person_repository_create(const char *type);

#endif /* PERSON_REPOSITORY_FACTORY_H */