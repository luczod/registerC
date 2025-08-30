#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person_controller_gtk.h"
#include "main_window.h"

#define PERSON_CONTROLLER_BUFFER_SEARCH 1024

static void person_controller_events_on_get(void *object);
static void person_controller_events_on_add(void *object, char *name, char *address, char *age);
static void person_controller_events_on_update(void *object, int id, char *name, char *address, char *age);
static void person_controller_events_on_delete(void *object, int id);
static void person_controller_events_on_search(void *object, const char *name);

static MAIN_WINDOW_T main_window;

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

        gtk_controller->events.object = gtk_controller;

        gtk_controller->events.on_get = person_controller_events_on_get;
        gtk_controller->events.on_add = person_controller_events_on_add;
        gtk_controller->events.on_update = person_controller_events_on_update;
        gtk_controller->events.on_delete = person_controller_events_on_delete;
        gtk_controller->events.on_search = person_controller_events_on_search;

        status = main_window_init(&main_window);

        gtk_controller->view = &main_window.base;
    }

    return status;
}

bool person_controller_gtk_open(void *object, PERSON_CONTROLLER_ARGS_T *args)
{
    bool status = false;

    MAIN_WINDOW_ARGS_T main_window_args;

    if (object != NULL && args != NULL && args->service != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        gtk_controller->service = args->service;

        main_window_args.argc = args->argc;
        main_window_args.argv = args->argv;
        main_window_args.con = &gtk_controller->events;

        status = main_window_open(&main_window, &main_window_args);
    }

    return status;
}

bool person_controller_gtk_run(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        status = main_window_run(&main_window);
    }

    return status;
}

bool person_controller_gtk_close(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_GTK_T *gtk_controller = (PERSON_CONTROLLER_GTK_T *)object;

        main_window_close(&main_window);

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

static void person_controller_events_on_get(void *object)
{
    PERSON_CONTROLLER_GTK_T *con = (PERSON_CONTROLLER_GTK_T *)object;
    PERSON_T *list = NULL;
    unsigned int amount = 0;

    con->service->base.getall(con->service->base.object, &list, &amount);

    con->view->set_all_persons(con->view->object, list, amount);

    free(list);
}

static void person_controller_events_on_add(void *object, char *name, char *address, char *age)
{
    PERSON_CONTROLLER_GTK_T *con = (PERSON_CONTROLLER_GTK_T *)object;
    PERSON_T p = person_create(name, address, atoi(age));

    con->service->repository->add(con->service->repository->object, &p);
}

static void person_controller_events_on_update(void *object, int id, char *name, char *address, char *age)
{
    PERSON_CONTROLLER_GTK_T *con = (PERSON_CONTROLLER_GTK_T *)object;
    PERSON_T p = person_create(name, address, atoi(age));
    p.id = id;

    con->service->repository->update(con->service->repository->object, &p);
}

static void person_controller_events_on_delete(void *object, int id)
{
    PERSON_CONTROLLER_GTK_T *con = (PERSON_CONTROLLER_GTK_T *)object;

    PERSON_T p = {.id = id};

    con->service->repository->remove(con->service->repository->object, &p);
}

static void person_controller_events_on_search(void *object, const char *name)
{

    char buffer[PERSON_CONTROLLER_BUFFER_SEARCH] = {0};
    MESSAGE_TYPE_T type = MESSAGE_INFO;
    DIALOG_BUTTON_T button_type = DIALOG_BUTTON_OK;

    PERSON_CONTROLLER_GTK_T *con = (PERSON_CONTROLLER_GTK_T *)object;

    char *message_found = "FOUND! - [ID: %d, NAME: %s, ADDRESS: %s, AGE: %d]";
    char *message_error_str = "Item NOT found!";

    PERSON_T p;
    strncpy(p.name, name, PERSON_NAME_LEN);

    bool status = con->service->repository->find(con->service->repository->object, &p);

    if (status == true)
    {
        snprintf(buffer, PERSON_CONTROLLER_BUFFER_SEARCH, message_found, p.id, p.name, p.address, p.age);
    }
    else
    {
        type = MESSAGE_ERROR;
        snprintf(buffer, PERSON_CONTROLLER_BUFFER_SEARCH, "%s", message_error_str);
    }

    con->view->show_dialog_message(con->view->object, buffer, type, button_type);
}
