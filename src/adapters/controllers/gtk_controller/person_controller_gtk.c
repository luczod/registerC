#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person_controller_gtk.h"

bool person_controller_gtk_init(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        memset(gtk_controller, 0, sizeof(PERSON_CONTROLLER_GTK_T));

        gtk_controller->base.object = gtk_controller;

        gtk_controller->base.init = person_controller_gtk_init;
        gtk_controller->base.open = person_controller_gtk_open;
        gtk_controller->base.run = person_controller_gtk_run;
        gtk_controller->base.close = person_controller_gtk_close;

        status = gtk_view_init(&gtk_controller->view);
    }

    return status;
}

bool person_controller_gtk_open(void *object, PERSON_CONTROLLER_ARGS_T *args)
{
    bool status = false;
    GTK_VIEW_ARGS_T gtk_view_args;

    if (object != NULL && args != NULL && args->service != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        gtk_controller->service = args->service;

        gtk_view_args.argc = args->argc;
        gtk_view_args.argv = args->argv;

        status = gtk_view_open(&gtk_controller->view, &gtk_view_args);
    }

    return status;
}

bool person_controller_gtk_run(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        status = gtk_view_run(&gtk_controller->view);
    }

    return status;
}

bool person_controller_gtk_close(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        gtk_view_close(&gtk_controller->view);

        memset(gtk_controller, 0, sizeof(PERSON_CONTROLLER_GTK_T));

        status = true;
    }
    return status;
}

PERSON_CONTROLLER_BASE_T person_controller_gtk_create(PERSON_CONTROLLER_ARGS_T *args)
{
    static PERSON_CONTROLLER_GTK_T gtk_controller;

    person_controller_gtk_init(&gtk_controller);
    person_controller_gtk_open(&gtk_controller, args);

    return gtk_controller.base;
}
