#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person_controller_webserver.h"
#include "handlers.h"

static HANDLER_LIST_T *person_controller_webserver_get_handler_list(PERSON_CONTROLLER_WEBSERVER_T *webserver_controller);

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
        webserver_controller->list = person_controller_webserver_get_handler_list(webserver_controller);

        WEBSERVER_ARGS_T web_args = {
            .port = args->port,
            .list = webserver_controller->list,
        };

        status = webserver_open(&webserver_controller->server, &web_args);
    }

    return status;
}

bool person_controller_webserver_run(void *object)
{
    PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    webserver_run(&webserver_controller->server);

    return true;
}

bool person_controller_webserver_close(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_WEBSERVER_T *webserver_controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

        webserver_close(&webserver_controller->server);

        free(webserver_controller->list);

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

static HANDLER_LIST_T *person_controller_webserver_get_handler_list(PERSON_CONTROLLER_WEBSERVER_T *webserver_controller)
{
    HANDLER_LIST_T *list = (HANDLER_LIST_T *)calloc(1, sizeof(HANDLER_LIST_T));

    list->handles[0].endpoint = HANDLER_ENDPOINT_INDEX;
    list->handles[0].handler = handler_index;
    list->handles[0].data = webserver_controller;

    list->handles[1].endpoint = HANDLER_ENDPOINT_VERSION;
    list->handles[1].handler = handler_version_request;
    list->handles[1].data = webserver_controller;

    list->handles[2].endpoint = HANDLER_ENDPOINT_PERSON;
    list->handles[2].handler = handler_requests;
    list->handles[2].data = webserver_controller;

    list->amount = 3;

    return list;
}
