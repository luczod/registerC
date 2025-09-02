#ifndef PERSON_CONTROLLER_BASE_H
#define PERSON_CONTROLLER_BASE_H

#include "person_service.h"

typedef struct PERSON_CONTROLLER_ARGS_T
{
    PERSON_SERVICE_T *service;
    int argc;
    char **argv;
    char *port;
} PERSON_CONTROLLER_ARGS_T;

typedef struct PERSON_CONTROLLER_BASE_T
{
    void *object;
    bool (*init)(void *object);
    bool (*open)(void *object, PERSON_CONTROLLER_ARGS_T *args);
    bool (*run)(void *object);
    bool (*close)(void *object);
} PERSON_CONTROLLER_BASE_T;

#endif /* PERSON_CONTROLLER_BASE_H */