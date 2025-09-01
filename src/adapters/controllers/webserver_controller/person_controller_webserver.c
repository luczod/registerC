#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person_controller_webserver.h"

typedef enum PERSON_CONTROLLER_OPTIONS
{
    person_add = 1,
    person_remove,
    person_update,
    person_find,
    person_getall,
    person_quit,
} PERSON_CONTROLLER_OPTIONS;

bool person_controller_webserver_init(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

        memset(webserver_controller, 0, sizeof(PERSON_CONTROLLER_WEBSERVER_T));

        webserver_controller->base.object = webserver_controller;

        webserver_controller->base.init = person_controller_webserver_init;
        webserver_controller->base.open = person_controller_webserver_open;
        webserver_controller->base.run = person_controller_webserver_run;
        webserver_controller->base.close = person_controller_webserver_close;

        status = webserver_init(&webserver_controller->server);
    }
    return status;
}

bool person_controller_webserver_open(void *object, PERSON_CONTROLLER_ARGS_T *args)
{
    bool status = false;

    if (object != NULL && args->service != NULL)
    {
        PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

        webserver_controller->service = args->service;

        WEBSERVER_ARGS_T web_args = {
            .port = "9090",
        };

        status = webserver_open(&webserver_controller->server, &web_args);
    }

    return status;
}

bool person_controller_webserver_run(void *object)
{
    PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    webserver_run(&webserver_controller->server);
    printf("Server started http://localhost:9090");

    return true;
}

bool person_controller_webserver_close(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

        webserver_close(&webserver_controller->server);
        memset(webserver_controller, 0, sizeof(PERSON_CONTROLLER_WEBSERVER_T));

        status = true;
    }
    return status;
}

PERSON_CONTROLLER_BASE_T person_controller_webserver_create(PERSON_CONTROLLER_ARGS_T *args)
{
    static PERSON_CONTROLLER_WEBSERVER_T webserver_controller;

    person_controller_webserver_init(&webserver_controller);
    person_controller_webserver_open(&webserver_controller, args);

    return webserver_controller.base;
}
