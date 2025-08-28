#include "person_controller_factory.h"
#include "person_controller_cli.h"

PERSON_CONTROLLER_BASE_T person_controller_factory_create(PERSON_CONTROLLER_TYPE_T type, PERSON_CONTROLLER_ARGS_T *args)
{
    PERSON_CONTROLLER_BASE_T controller_base;

    if (type == PERSON_CONTROLLER_TYPE_CLI)
    {
        controller_base = person_controller_cli_create(args->service);
    }

    return controller_base;
}
