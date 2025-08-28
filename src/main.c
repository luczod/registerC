#include <stdio.h>
#include <stdlib.h>
#include "person_service.h"
#include "person_repository_factory.h"
#include "person_controller_factory.h"

int main(void)
{

    PERSON_REPOSITORY_BASE_T repository = person_repository_create(PERSON_REPOSITORY_TYPE_SQLITE);

    PERSON_SERVICE_T service;
    person_service_init(&service);
    person_service_open(&service, (PERSON_REPOSITORY_BASE_T *)&repository);

    PERSON_CONTROLLER_BASE_T controller = person_controller_factory_create(PERSON_CONTROLLER_TYPE_CLI, &service);
    controller.run(controller.object);

    controller.close(controller.object);
    person_service_close(&service);

    return EXIT_SUCCESS;
}
