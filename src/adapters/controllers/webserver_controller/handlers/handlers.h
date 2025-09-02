#ifndef HANDLERS_H
#define HANDLERS_H

#include "civetweb.h"
#include "cJSON.h"
#include "person.h"

#define HANDLER_WEBSERVER_AMOUNT 10
#define HANDLER_REQUESTS_AMOUNT 5

#define HANDLER_REQUESTS_GET "GET"
#define HANDLER_REQUESTS_POST "POST"
#define HANDLER_REQUESTS_PUT "PUT"
#define HANDLER_REQUESTS_DELETE "DELETE"

#define HANDLER_ENDPOINT_PERSON "/person"
#define HANDLER_ENDPOINT_VERSION "/version"
#define HANDLER_ENDPOINT_INDEX "/"

typedef int (*handler_request_t)(struct mg_connection *conn, void *data);

typedef struct HANDLER_T
{
    const char *endpoint;
    handler_request_t handler;
    void *data;
} HANDLER_T;

typedef struct HANDLER_LIST_T
{
    HANDLER_T handles[HANDLER_WEBSERVER_AMOUNT];
    unsigned char amount;
} HANDLER_LIST_T;

typedef struct HANDLER_REQUEST_T
{
    const char *method;
    handler_request_t handler;
} HANDLER_REQUEST_MAP_T;

typedef struct REQUESTS_MAP_T
{
    HANDLER_REQUEST_MAP_T requests[HANDLER_REQUESTS_AMOUNT];
    unsigned char amount;
} REQUESTS_MAP_T;

int handler_index(struct mg_connection *conn, void *data);
int handler_requests(struct mg_connection *conn, void *data);
int handler_version_request(struct mg_connection *conn, void *data);
int send_json(struct mg_connection *conn, cJSON *json_obj, int status);

int handler_get(struct mg_connection *conn, void *data);
int handler_post(struct mg_connection *conn, void *data);
int handler_put(struct mg_connection *conn, void *data);
int handler_delete(struct mg_connection *conn, void *data);

cJSON *serialize_person_list(PERSON_T *list, unsigned int amount);
cJSON *serialize_person(cJSON *obj, PERSON_T *person);

cJSON *serialize_error(const char *error, const char *hint);

#endif /* HANDLERS_H */