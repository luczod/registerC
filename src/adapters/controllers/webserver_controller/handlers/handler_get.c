#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include "webserver.h"
#include "person_controller_webserver.h"

static cJSON *handler_get_all(void *object);

int handler_get(struct mg_connection *conn, void *data)
{
    int status = 200;
    cJSON *json;

    json = handler_get_all(data);

    if (json == NULL)
    {
        json = serialize_error("No content", "There is no records");
        status = 404;
    }

    send_json(conn, json, status);
    cJSON_Delete(json);

    return status;
}

static cJSON *handler_get_all(void *object)
{
    cJSON *json;

    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    PERSON_T *list = NULL;
    unsigned int amount = 0;

    controller->service->base.getall(controller->service->base.object, &list, &amount);

    json = serialize_person_list(list, amount);

    free(list);

    return json;
}
