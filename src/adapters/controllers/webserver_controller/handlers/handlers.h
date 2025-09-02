#ifndef HANDLERS_H
#define HANDLERS_H

#include "civetweb.h"
#include "cJSON.h"

#define WEBSERVER_HANDLER_AMOUNT 10

typedef int (*handler_func_t)(struct mg_connection *conn, void *data);

typedef struct
{
    const char *endpoint;
    handler_func_t handler;
    void *data;
} HANDLER_T;

typedef struct
{
    HANDLER_T handles[WEBSERVER_HANDLER_AMOUNT];
    unsigned char amount;
} HANDLER_LIST_T;

int handler_index(struct mg_connection *conn, void *data);
int handler_version_request(struct mg_connection *conn, void *data);
int send_json(struct mg_connection *conn, cJSON *json_obj);

#endif /* HANDLERS_H */