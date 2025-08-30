
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <stdbool.h>
#include "insert_dialog.h"
#include "edit_dialog.h"
#include "view_base.h"
#include "person_controller_events_base.h"

typedef struct MAIN_WINDOW_WIDGETS_T
{
    void *window;
    void *input_search;
    void *person_model;
    void *person_treeview;
    void *bt_insert;
    void *bt_edit;
    void *bt_delete;
    void *bt_find;
} MAIN_WINDOW_WIDGETS_T;

typedef struct MAIN_WINDOW_T
{
    VIEW_BASE_T base;
    MAIN_WINDOW_WIDGETS_T *widgets;
    INSERT_DIALOG_T insert;
    EDIT_DIALOG_T edit;
    PERSON_CONTROLLER_EVENTS_BASE_T *con;
    int argc;
    char **argv;
} MAIN_WINDOW_T;

typedef struct MAIN_WINDOW_ARGS_T
{
    int argc;
    char **argv;
    PERSON_CONTROLLER_EVENTS_BASE_T *con;
} MAIN_WINDOW_ARGS_T;

bool main_window_init(MAIN_WINDOW_T *window);
bool main_window_open(MAIN_WINDOW_T *window, MAIN_WINDOW_ARGS_T *args);
bool main_window_run(MAIN_WINDOW_T *window);
bool main_window_close(MAIN_WINDOW_T *window);

#endif /* MAIN_WINDOW_H */
