#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include "webserver.h"
#include "handlers.h"
#include "person_controller_webserver.h"

static cJSON *handler_update(void *object, char *buffer, int size, int id);

int handler_put(struct mg_connection *conn, void *data)
{
    int status = 401;
    cJSON *json;
    int size;
    char buffer[1024] = {0};
    char param[128] = {0};

    const struct mg_request_info *ri = mg_get_request_info(conn);

    if (ri->query_string == NULL)
    {
        json = serialize_message("Bad Request", "no body");
        send_json(conn, json, status);
        cJSON_Delete(json);

        return status;
    }

    mg_get_var(ri->query_string, strlen(ri->query_string), "id", param, 128);
    if (strlen(param) > 0)
    {
        size = mg_read(conn, buffer, sizeof(buffer) - 1);
        buffer[size] = 0;
        json = handler_update(data, buffer, size, atoi(param));
    }

    if (json != NULL)
        status = 200;
    else
    {
        json = serialize_message("No content", "There is no records");
        status = 404;
    }

    send_json(conn, json, status);
    cJSON_Delete(json);

    return status;
}

static cJSON *handler_update(void *object, char *buffer, int size, int id)
{
    PERSON_T person;
    cJSON *json = NULL;
    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    if (deserialize_person(buffer, &person) == true)
    {
        person.id = id;
        bool person_exists = controller->service->repository->update(controller->service->repository->object, &person);

        if (person_exists)
        {
            json = serialize_message("Accpeted", "Register Updated!");
        }
    }

    return json;
}
