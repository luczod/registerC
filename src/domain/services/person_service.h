#ifndef PERSON_SERVICE_H
#define PERSON_SERVICE_H

#include "person_repository_base.h"
#include "person_service_base.h"

typedef struct PERSON_SERVICE_T
{
    PERSON_SERVICE_BASE_T base;
    PERSON_REPOSITORY_BASE_T *repository;
} PERSON_SERVICE_T;

bool person_service_init(PERSON_SERVICE_T *service);
bool person_service_open(PERSON_SERVICE_T *service, PERSON_REPOSITORY_BASE_T *repositroy);
bool person_service_close(PERSON_SERVICE_T *service);

#endif /* PERSON_SERVICE_H */