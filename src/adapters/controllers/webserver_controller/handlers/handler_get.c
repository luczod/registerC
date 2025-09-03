#include <string.h>
#include <cJSON.h>
#include <stdlib.h>
#include "webserver.h"
#include "person_controller_webserver.h"

static cJSON *handler_get_all(void *object);
static cJSON *handler_find(void *object, const char *name);

int handler_get(struct mg_connection *conn, void *data)
{
    int status = 200;
    cJSON *json;
    char buffer[1024];

    const struct mg_request_info *ri = mg_get_request_info(conn);

    if (ri->query_string != NULL)
    {
        mg_get_var(ri->query_string, strlen(ri->query_string), "name", buffer, 1024);
        json = handler_find(data, buffer);
    }
    else
    {
        json = handler_get_all(data);
    }

    if (json == NULL)
    {
        json = serialize_message("No content", "There is no records");
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

static cJSON *handler_find(void *object, const char *name)
{
    cJSON *json = NULL;

    PERSON_CONTROLLER_WEBSERVER_T *controller = (PERSON_CONTROLLER_WEBSERVER_T *)object;

    PERSON_T person = person_create(name, NULL, 0);

    bool person_exists = controller->service->base.find(controller->service->base.object, &person);

    if (strlen(name) > 0 && person_exists)
    {
        json = serialize_person(NULL, &person);
    };

    return json;
}
