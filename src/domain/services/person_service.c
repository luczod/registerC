#include <string.h>
#include <stdlib.h>
#include "person_service.h"

static bool person_service_add(void *object, PERSON_T *person);
static bool person_service_remove(void *object, PERSON_T *person);
static bool person_service_update(void *object, PERSON_T *person);
static bool person_service_find(void *object, PERSON_T *person);
static bool person_service_getall(void *object, PERSON_T **person_list, unsigned int *amount);

bool person_service_init(PERSON_SERVICE_T *service)
{
    bool status = false;

    if (service != NULL)
    {
        memset(service, 0, sizeof(PERSON_SERVICE_T));

        service->base.object = service;

        service->base.add = person_service_add;
        service->base.remove = person_service_remove;
        service->base.update = person_service_update;
        service->base.find = person_service_find;
        service->base.getall = person_service_getall;

        status = true;
    }

    return status;
}

bool person_service_open(PERSON_SERVICE_T *service, PERSON_REPOSITORY_BASE_T *repositroy)
{
    bool status = false;
    if (service != NULL && repositroy != NULL)
    {
        service->repository = repositroy;
        status = true;
    }

    return status;
}

bool person_service_close(PERSON_SERVICE_T *service)
{
    bool status = false;

    if (service != NULL)
    {
        memset(service, 0, sizeof(PERSON_SERVICE_T));

        status = true;
    }
    return status;
}

/* INTERFACES */
static bool person_service_add(void *object, PERSON_T *person)
{
    bool status = false;
    PERSON_SERVICE_T *sevice = (PERSON_SERVICE_T *)object;

    status = sevice->repository->add(sevice->repository->object, person);

    return status;
}

static bool person_service_remove(void *object, PERSON_T *person)
{
    bool status = false;
    PERSON_SERVICE_T *sevice = (PERSON_SERVICE_T *)object;

    status = sevice->repository->remove(sevice->repository->object, person);

    return status;
}

static bool person_service_update(void *object, PERSON_T *person)
{
    bool status = false;
    PERSON_SERVICE_T *sevice = (PERSON_SERVICE_T *)object;

    status = sevice->repository->update(sevice->repository->object, person);

    return status;
}

static bool person_service_find(void *object, PERSON_T *person)
{
    bool status = false;
    PERSON_SERVICE_T *sevice = (PERSON_SERVICE_T *)object;

    status = sevice->repository->find(sevice->repository->object, person);

    return status;
}

static bool person_service_getall(void *object, PERSON_T **person_list, unsigned int *amount)
{
    bool status = false;
    PERSON_SERVICE_T *sevice = (PERSON_SERVICE_T *)object;

    status = sevice->repository->getall(sevice->repository->object, person_list, amount);

    return status;
}
