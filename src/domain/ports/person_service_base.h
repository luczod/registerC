#ifndef PERSON_SERVICE_BASE_H
#define PERSON_SERVICE_BASE_H

#include <stdbool.h>
#include "person.h"

typedef struct PERSON_SERVICE_BASE
{
    void *object;
    bool (*add)(void *object, PERSON_T *person);
    bool (*remove)(void *object, PERSON_T *person);
    bool (*update)(void *object, PERSON_T *person);
    bool (*find)(void *object, PERSON_T *person);
    bool (*getall)(void *object, PERSON_T **person_list, unsigned int *amount);
} PERSON_SERVICE_BASE_T;

#endif /* PERSON_SERVICE_BASE_H */