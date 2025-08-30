#ifndef INSERT_DIALOG_H
#define INSERT_DIALOG_H

#include <stdbool.h>
#include "person_controller_events_base.h"

typedef struct INSERT_DIALOG_WIDGET_T
{
    void *dialog;
    void *txt_name;
    void *txt_address;
    void *txt_age;
    void *bt_confirm;
    void *bt_cancel;
} INSERT_DIALOG_WIDGET_T;

typedef struct INSERT_DIALOG_T
{
    void *parent;
    INSERT_DIALOG_WIDGET_T *widgets;
    PERSON_CONTROLLER_EVENTS_BASE_T *con;
} INSERT_DIALOG_T;

typedef struct INSERT_DIALOG_ARGS_T
{
    void *parent;
    int argc;
    char **argv;
    PERSON_CONTROLLER_EVENTS_BASE_T *con;
} INSERT_DIALOG_ARGS_T;

bool insert_dialog_init(INSERT_DIALOG_T *dialog);
bool insert_dialog_open(INSERT_DIALOG_T *dialog, INSERT_DIALOG_ARGS_T *args);
bool insert_dialog_run(INSERT_DIALOG_T *dialog);
bool insert_dialog_close(INSERT_DIALOG_T *dialog);

#endif /* INSERT_DIALOG_H */