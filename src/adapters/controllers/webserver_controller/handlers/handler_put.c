#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include "webserver.h"
#include "person_controller_webserver.h"

static cJSON *handler_update(void *object, char *buffer, int size);

int handler_put(struct mg_connection *conn, void *data)
{
    int status;
    char buffer[1024];
    cJSON *json;

    int size = mg_read(conn, buffer, sizeof(buffer) - 1);
    buffer[size] = 0;

    json = handler_update(data, buffer, size);

    if (json != NULL)
    {
        status = 200;
    }
    else
    {
        json = serialize_message("Bad Request", "missing keys in body");
        status = 401;
    }

    send_json(conn, json, status);

    return status;
}

static cJSON *handler_update(void *object, char *buffer, int size)
{
    PERSON_T person;
    cJSON *json = NULL;

    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    bool person_exists = deserialize_person_with_id(buffer, &person);

    if (!person_exists || person.id == 0)
    {
        return json;
    }

    if (person_exists && person.id > 0)
    {
        if (controller->service->base.update(controller->service->base.object, &person) == true)
            json = serialize_message("Accpeted", "Register Updated!");
    }

    return json;
}
