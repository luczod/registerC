#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include "webserver.h"
#include "person_controller_webserver.h"

static cJSON *handler_update(void *object, char *buffer, int size);

int handler_post(struct mg_connection *conn, void *data)
{
    int status;
    char buffer[1024];
    cJSON *json;

    int size = mg_read(conn, buffer, sizeof(buffer) - 1);
    buffer[size] = 0;

    json = handler_update(data, buffer, size);

    if (json != NULL)
    {
        status = 201;
    }
    else
    {
        json = serialize_message("Not modified", "Content not created");
        status = 301;
    }

    send_json(conn, json, status);

    return status;
}

static cJSON *handler_update(void *object, char *buffer, int size)
{
    PERSON_T person;
    cJSON *json = NULL;

    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    if (deserialize_person(buffer, &person) == true)
    {
        if (controller->service->base.add(controller->service->base.object, &person) == true)
            json = serialize_message("Created", "Register created");
    }

    return json;
}
