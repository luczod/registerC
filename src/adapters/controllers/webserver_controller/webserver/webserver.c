#include <string.h>
#include <webserver.h>
#include <cJSON.h>
#include <unistd.h>

static int log_message(const struct mg_connection *conn, const char *message);
static bool webserver_handler_register(WEBSERVER_T *webserber);

bool webserver_init(WEBSERVER_T *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        memset(webserver, 0, sizeof(WEBSERVER_T));
        mg_init_library(MG_FEATURES_DEFAULT);

        webserver->mg_callbacks.log_message = log_message;
        status = true;
    }

    return status;
}

bool webserver_open(WEBSERVER_T *webserver, WEBSERVER_ARGS_T *args)
{
    bool status = false;

    if (webserver != NULL && args != NULL && args->list != NULL && args->list->amount > 0)
    {
        webserver->port = args->port;
        webserver->list = args->list;
        status = true;
    }

    return status;
}

bool webserver_run(WEBSERVER_T *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        const char *options[] =
            {
                "listening_ports",
                webserver->port,
                "request_timeout_ms",
                "1000",
                "error_log_file",
                "error.log",
                "enable_auth_domain_check",
                "no",
                "document_root",
                "./assets",
                0,
            };

        webserver->mg_context = mg_start(&webserver->mg_callbacks, 0, options);

        if (webserver->mg_context != NULL)
        {
            status = webserver_handler_register(webserver);
            while (status)
                usleep(1);
        }
    }
    return status;
}

bool webserver_close(WEBSERVER_T *webserver)
{
    bool status = false;

    if (webserver != NULL)
    {
        mg_stop(webserver->mg_context);
        memset(webserver, 0, sizeof(WEBSERVER_T));
        status = true;
    }

    return status;
}

int log_message(const struct mg_connection *conn, const char *message)
{
    fprintf(stderr, "LOG: %s\n", message);
    return 0;
}

bool webserver_handler_register(WEBSERVER_T *webserver)
{
    bool status = false;

    for (unsigned char i = 0; i < webserver->list->amount; i++)
    {
        HANDLER_T *h = &webserver->list->handles[i];
        mg_set_request_handler(webserver->mg_context,
                               h->endpoint, h->handler, h->data);
    }

    status = true;

    return status;
}
