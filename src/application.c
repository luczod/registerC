#include <stdbool.h>
#include "application.h"

bool application_init(APPLICATION_T *app, VIEW_BASE *view, REPOSITORY_BASE *repository)
{
    bool status = false;

    if (app && view && repository)
    {
        app->repository = repository;
        app->view = view;

        status = true;
    }

    return status;
}

bool application_run(APPLICATION_T *app)
{
    bool status = false;
    do
    {
        if (app->view->init(app->view->object) == false)
            break;

        if (app->view->exec(app->view->object, app->repository) == false)
            break;

        status = true;

    } while (false);

    return status;
}