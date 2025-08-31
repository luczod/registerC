#ifndef PERSON_CONTROLLER_WEBSERVER_H
#define PERSON_CONTROLLER_WEBSERVER_H

#include "person_controller_base.h"
#include "person_service.h"
#include "webserver.h"

typedef struct PERSON_CONTROLLER_WEBSERVER_T
{
    PERSON_CONTROLLER_BASE_T base;
    PERSON_SERVICE_T *service;
    WEBSERVER_T server;
} PERSON_CONTROLLER_WEBSERVER_T;

bool person_controller_webserver_init(void *object);
bool person_controller_webserver_open(void *object, PERSON_CONTROLLER_ARGS_T *args);
bool person_controller_webserver_run(void *object);
bool person_controller_webserver_close(void *object);

PERSON_CONTROLLER_BASE_T person_controller_webserver_create(PERSON_CONTROLLER_ARGS_T *args);

#endif /* PERSON_CONTROLLER_WEBSERVER_H */