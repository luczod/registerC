#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <stdbool.h>
#include <civetweb.h>

typedef struct WEBSERVER_T
{
    struct mg_context *mg_context;
    struct mg_callbacks mg_callbacks;
    char *port;
} WEBSERVER_T;

typedef struct WEBSERVER_ARGS_T
{
    char *port;
} WEBSERVER_ARGS_T;

bool webserver_init(WEBSERVER_T *webserver);
bool webserver_open(WEBSERVER_T *webserver, WEBSERVER_ARGS_T *args);
bool webserver_run(WEBSERVER_T *webserver);
bool webserver_close(WEBSERVER_T *webserver);

#endif /* WEBSERVER_H */