#ifndef EDIT_DIALOG_H
#define EDIT_DIALOG_H

#include <stdbool.h>

typedef struct EDIT_DIALOG_WIDGET_T
{
    void *dialog;
    void *txt_name;
    void *txt_address;
    void *txt_age;
    void *bt_confirm;
    void *bt_cancel;
} EDIT_DIALOG_WIDGET_T;

typedef struct EDIT_DIALOG_T
{
    void *parent;
    EDIT_DIALOG_WIDGET_T *widgets;
} EDIT_DIALOG_T;

typedef struct EDIT_DIALOG_ARGS_T
{
    void *parent;
    int argc;
    char **argv;
} EDIT_DIALOG_ARGS_T;

bool edit_dialog_init(EDIT_DIALOG_T *dialog);
bool edit_dialog_open(EDIT_DIALOG_T *dialog, EDIT_DIALOG_ARGS_T *args);
bool edit_dialog_run(EDIT_DIALOG_T *dialog);
bool edit_dialog_close(EDIT_DIALOG_T *dialog);

#endif /* EDIT_DIALOG_H */