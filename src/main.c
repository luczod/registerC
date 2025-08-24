#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_register.h"
#include "repository_factory.h"
#include "application.h"
#include "view_factory.h"

#define REPOSITORY_TYPE "sqlite"
#define VIEW_TYPE "cli"

int main(void)
{

    REPOSITORY_BASE *repository = NULL;
    VIEW_BASE *view = NULL;
    APPLICATION_T app;
    bool ret;

    do
    {
        repository = repopository_create(REPOSITORY_TYPE);
        if (repository == NULL)
            break;

        view = view_create(VIEW_TYPE);
        if (view == NULL)
            break;

        ret = application_init(&app, view, repository);
        if (ret == false)
            break;

        application_run(&app);

    } while (false);

    repository_destroy(REPOSITORY_TYPE, repository);
    view_destroy(VIEW_TYPE, view);

    return EXIT_SUCCESS;
}
