#include <stdlib.h>
#include <string.h>
#include "person_controller_cli.h"

typedef enum
{
    person_add = 1,
    person_remove,
    person_update,
    person_find,
    person_getall,
} PERSON_CONTROLLER_OPTIONS;

static void *person_controller_cli_on_selected(uint8_t index, void *data);

static bool person_controller_cli_add(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_remove(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_update(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_find(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_getall(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_print(PERSON_CONTROLLER_CLI_T *cli_controller, const PERSON_T **person_list, unsigned int *amount);

bool person_controller_cli_init(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)object;

        memset(cli_controller, 0, sizeof(PERSON_CONTROLLER_CLI_T));

        cli_controller->base.init = person_controller_cli_init;
        cli_controller->base.open = person_controller_cli_open;
        cli_controller->base.run = person_controller_cli_run;
        cli_controller->base.close = person_controller_cli_close;

        cli_init(&cli_controller->cli);

        cli_controller->cli.on_selected = person_controller_cli_on_selected;
    }
    return status;
}

bool person_controller_cli_open(void *object, PERSON_SERVICE_T *service)
{
}

bool person_controller_cli_run(void *object)
{
}

bool person_controller_cli_close(void *object)
{
}

PERSON_CONTROLLER_BASE_T person_controller_cli_create(PERSON_SERVICE_T *service)
{
}

static void *person_controller_cli_on_selected(uint8_t index, void *data)
{
    PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)data;
}

static bool person_controller_cli_add(PERSON_CONTROLLER_CLI_T *cli_controller)
{
}

static bool person_controller_cli_remove(PERSON_CONTROLLER_CLI_T *cli_controller)
{
}

static bool person_controller_cli_update(PERSON_CONTROLLER_CLI_T *cli_controller)
{
}

static bool person_controller_cli_find(PERSON_CONTROLLER_CLI_T *cli_controller)
{
}

static bool person_controller_cli_getall(PERSON_CONTROLLER_CLI_T *cli_controller)
{
}

bool person_controller_cli_print(PERSON_CONTROLLER_CLI_T *cli_controller, const PERSON_T **person_list, unsigned int *amount)
{
    return false;
}
