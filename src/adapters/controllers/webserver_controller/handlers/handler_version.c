
#include <string.h>
#include <cJSON.h>
#include "webserver.h"
#include "handlers.h"

int handler_version_request(struct mg_connection *conn, void *data)
{
    int status = 200;
    cJSON *obj = cJSON_CreateObject();

    if (!obj)
    {
        mg_send_http_error(conn, 500, "Server Error");
        status = 500;
    }

    cJSON_AddStringToObject(obj, "version", CIVETWEB_VERSION);
    send_json(conn, obj, status);

    cJSON_Delete(obj);

    return status;
}