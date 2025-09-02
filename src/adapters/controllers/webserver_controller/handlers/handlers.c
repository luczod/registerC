#include <string.h>
#include <cJSON.h>
#include "webserver.h"
#include "handlers.h"

int handler_requests(struct mg_connection *conn, void *data)
{
    const struct mg_request_info *ri = mg_get_request_info(conn);

    static REQUESTS_MAP_T map = {
        .requests =
            {
                {.method = HANDLER_REQUESTS_GET, .handler = handler_get},
                {.method = HANDLER_REQUESTS_POST, .handler = handler_post},
                {.method = HANDLER_REQUESTS_PUT, .handler = handler_put},
                {.method = HANDLER_REQUESTS_DELETE, .handler = handler_delete},

            },
        .amount = 4,
    };

    for (unsigned char i = 0; i < map.amount; i++)
    {
        HANDLER_REQUEST_MAP_T *rm = &map.requests[i];

        if (strcmp(ri->request_method, rm->method) == 0)
        {
            return rm->handler(conn, data);
        }
    }

    mg_send_http_error(conn, 405, "Method not allowed");

    return 405;
}

int send_json(struct mg_connection *conn, cJSON *json_obj, int status)
{
    char *json_string = cJSON_PrintUnformatted(json_obj);
    size_t json_str_len = strlen(json_string);
    char json_buffer[32] = {0};
    snprintf(json_buffer, 32, "%lu", json_str_len);

    mg_response_header_start(conn, status);

    mg_response_header_add(conn, "Content-Type",
                           "application/json; charset=utf-8",
                           -1);

    mg_response_header_add(conn, "Content-Length", json_buffer, -1);

    mg_response_header_send(conn);

    mg_write(conn, json_string, json_str_len);

    cJSON_free(json_string);

    return (int)json_str_len;
}

cJSON *serialize_person_list(PERSON_T *list, unsigned int amount)
{
    cJSON *obj = cJSON_CreateObject();
    cJSON *array = NULL;

    if (obj != NULL)
    {
        array = cJSON_AddArrayToObject(obj, "person");
        if (array != NULL)
        {
            for (unsigned int i = 0; i < amount; i++)
                serialize_person(array, &list[i]);
        }
    }

    return obj;
}

cJSON *serialize_person(cJSON *obj, PERSON_T *person)
{
    cJSON *person_json = NULL;
    cJSON *name = NULL;
    cJSON *address = NULL;
    cJSON *age = NULL;
    cJSON *id = NULL;

    person_json = cJSON_CreateObject();

    if (person_json != NULL)
    {
        id = cJSON_CreateNumber(person->id);
        cJSON_AddItemToObject(person_json, "id", id);

        if (strlen(person->name) > 0)
        {
            name = cJSON_CreateString(person->name);
            cJSON_AddItemToObject(person_json, "name", name);
        }

        if (strlen(person->address) > 0)
        {
            address = cJSON_CreateString(person->address);
            cJSON_AddItemToObject(person_json, "address", address);
        }

        if (person->age > 0)
        {
            age = cJSON_CreateNumber(person->age);
            cJSON_AddItemToObject(person_json, "age", age);
        }

        if (obj != NULL)
            cJSON_AddItemToArray(obj, person_json);
    }

    return person_json;
}

cJSON *serialize_error(const char *error, const char *hint)
{
    cJSON *json = cJSON_CreateObject();

    if (json != NULL)
    {
        cJSON_AddStringToObject(json, "error", error);
        cJSON_AddStringToObject(json, "hint", hint);
    }

    return json;
}
