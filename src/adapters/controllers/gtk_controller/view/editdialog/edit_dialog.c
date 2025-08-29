#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "edit_dialog.h"

static bool edit_dialog_graphics_init(EDIT_DIALOG_T *dialog);

bool edit_dialog_init(EDIT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        memset(dialog, 0, sizeof(EDIT_DIALOG_T));
        status = true;
    }

    return status;
}

bool edit_dialog_open(EDIT_DIALOG_T *dialog, EDIT_DIALOG_ARGS_T *args)
{
    bool status = false;

    if (dialog != NULL && args != NULL)
    {
        status = edit_dialog_graphics_init(dialog);
    }

    return status;
}

bool edit_dialog_run(EDIT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        gtk_dialog_run(GTK_DIALOG(dialog->widgets->dialog));
        status = true;
    }

    return status;
}

bool edit_dialog_close(EDIT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        g_slice_free(EDIT_DIALOG_WIDGET_T, dialog->widgets);
        memset(dialog, 0, sizeof(EDIT_DIALOG_T));
        status = true;
    }

    return status;
}

bool edit_dialog_graphics_init(EDIT_DIALOG_T *dialog)
{
    GtkBuilder *builder;
    // GError *err;

    dialog->widgets = g_slice_new(EDIT_DIALOG_WIDGET_T);

    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "bin/resources/edit_window.glade", NULL);

    dialog->widgets->dialog = GTK_WIDGET(gtk_builder_get_object(builder, "edit_window"));
    dialog->widgets->txt_name = GTK_WIDGET(gtk_builder_get_object(builder, "txt_name"));
    dialog->widgets->txt_address = GTK_WIDGET(gtk_builder_get_object(builder, "txt_address"));
    dialog->widgets->txt_age = GTK_WIDGET(gtk_builder_get_object(builder, "txt_age"));
    dialog->widgets->bt_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "bt_cancel"));
    dialog->widgets->bt_confirm = GTK_WIDGET(gtk_builder_get_object(builder, "bt_confirm"));

    gtk_builder_connect_signals(builder, dialog);

    g_object_unref(builder);

    return true;
}

void on_edit_window_destroy(void)
{
}

void on_bt_edit_confirm_clicked(GtkButton *bt_confirm, void *data)
{
    printf("--- confirm ----\n");

    // EDIT_DIALOG_T *dialog = (EDIT_DIALOG_T *)data;
}

void on_bt_edit_cancel_clicked(GtkButton *bt_cancel, void *data)
{
    printf("--- cancel ----\n");

    EDIT_DIALOG_T *dialog = (EDIT_DIALOG_T *)data;

    gtk_widget_destroy(GTK_WIDGET(dialog->widgets->dialog));
}
