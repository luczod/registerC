#include <stdio.h>
#include <stdlib.h>
#include "person_service.h"
#include "person_repository_factory.h"
#include "person_controller_factory.h"
#include "configuration.h"

int main(int argc, char *argv[])
{
    CONFIGURATION_T conf;

    configuration_ini(&conf);

    if (configuration_load(&conf) == false)
    {
        printf("Ini File not found!");

        return EXIT_FAILURE;
    }

    PERSON_REPOSITORY_BASE_T repository = person_repository_create(conf.repository_type);

    PERSON_SERVICE_T service;
    person_service_init(&service);
    person_service_open(&service, (PERSON_REPOSITORY_BASE_T *)&repository);

    PERSON_CONTROLLER_ARGS_T args = {
        .argc = argc,
        .argv = argv,
        .service = &service,
    };

    PERSON_CONTROLLER_BASE_T controller = person_controller_factory_create(conf.controller_type, &args);
    controller.run(controller.object);

    controller.close(controller.object);
    person_service_close(&service);

    return EXIT_SUCCESS;
}
