#ifndef PERSON_CONTROLLER_CLI_H
#define PERSON_CONTROLLER_CLI_H

#include "person_controller_base.h"
#include "cli/cli.h"

typedef struct PERSON_CONTROLLER_CLI_T
{
    PERSON_CONTROLLER_BASE_T base;
    PERSON_SERVICE_T *service;
    CLI_T cli;
} PERSON_CONTROLLER_CLI_T;

bool person_controller_cli_init(void *object);
bool person_controller_cli_open(void *object, PERSON_SERVICE_T *service);
bool person_controller_cli_run(void *object);
bool person_controller_cli_close(void *object);

PERSON_CONTROLLER_BASE_T person_controller_cli_create(PERSON_SERVICE_T *service);

#endif /* PERSON_CONTROLLER_CLI_H */
