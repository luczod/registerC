#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include <stdio.h>
#include "webserver.h"
#include "person_controller_webserver.h"

static cJSON *handler_remove(void *object, int id);

int handler_delete(struct mg_connection *conn, void *data)
{
    int status = 200;
    cJSON *json;
    char buffer[1024] = {0};

    const struct mg_request_info *ri = mg_get_request_info(conn);

    if (ri->query_string == NULL)
    {
        json = serialize_error("Bad Request", "/person?id<number>");
        status = 404;
        send_json(conn, json, status);
        cJSON_Delete(json);

        return status;
    }

    mg_get_var(ri->query_string, strlen(ri->query_string), "id", buffer, 1024);
    json = handler_remove(data, atoi(buffer));

    if (json != NULL)
        status = 200;
    else
    {
        json = serialize_error("No content", "There is no records");
        status = 404;
    }

    send_json(conn, json, status);
    cJSON_Delete(json);

    return status;
}

static cJSON *handler_remove(void *object, int id)
{
    cJSON *json = NULL;

    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    PERSON_T person = {.id = id};
    bool person_exists = controller->service->repository->remove(controller->service->repository->object, &person);

    if (person_exists)
    {
        json = serialize_person(NULL, &person);
    };

    return json;
}
