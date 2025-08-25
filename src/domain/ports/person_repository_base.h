#ifndef PERSON_REPOSITORY_BASE_H
#define PERSON_REPOSITORY_BASE_H

#include <stdbool.h>
#include "person.h"

typedef struct PERSON_REPOSITORY_BASE
{
    void *object;
    bool (*add)(void *object, PERSON_T *person);
    bool (*remove)(void *object, PERSON_T *person);
    bool (*update)(void *object, PERSON_T *person);
    bool (*find)(void *object, PERSON_T *person);
    bool (*getall)(void *object, PERSON_T **person_list, unsigned int *amount);
} PERSON_REPOSITORY_BASE_T;

// void *object in a struct works like a inheritance/type for C

#endif /* PERSON_REPOSITORY_BASE_H */