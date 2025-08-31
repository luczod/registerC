#include <string.h>
#include "person_controller_factory.h"
#include "person_controller_cli.h"
#include "person_controller_gtk.h"
#include "person_controller_webserver.h"
#include "configuration.h"

PERSON_CONTROLLER_BASE_T person_controller_factory_create(const char *type, PERSON_CONTROLLER_ARGS_T *args)
{
    PERSON_CONTROLLER_BASE_T controller_base;

    if (strcmp(type, CONFIGURATION_CONTROLLER_TYPE_CLI) == 0)
    {
        controller_base = person_controller_cli_create(args);
    }
    else if (strcmp(type, CONFIGURATION_CONTROLLER_TYPE_GTK) == 0)
    {
        controller_base = person_controller_gtk_create(args);
    }
    else if (strcmp(type, CONFIGURATION_CONTROLLER_TYPE_WEBSERVER) == 0)
    {
        controller_base = person_controller_webserver_create(args);
    }

    return controller_base;
}
