#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "insert_dialog.h"

static bool insert_dialog_graphics_init(INSERT_DIALOG_T *dialog);

bool insert_dialog_init(INSERT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        memset(dialog, 0, sizeof(INSERT_DIALOG_T));
        status = true;
    }

    return status;
}

bool insert_dialog_open(INSERT_DIALOG_T *dialog, INSERT_DIALOG_ARGS_T *args)
{
    bool status = false;

    if (dialog != NULL && args != NULL)
    {
        status = insert_dialog_graphics_init(dialog);
    }

    return status;
}

bool insert_dialog_run(INSERT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        gtk_dialog_run(GTK_DIALOG(dialog->widgets->dialog));
        status = true;
    }

    return status;
}

bool insert_dialog_close(INSERT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        g_slice_free(INSERT_DIALOG_WIDGET_T, dialog->widgets);
        memset(dialog, 0, sizeof(INSERT_DIALOG_T));
        status = true;
    }

    return status;
}

bool insert_dialog_graphics_init(INSERT_DIALOG_T *dialog)
{
    GtkBuilder *builder;
    // GError *err;

    dialog->widgets = g_slice_new(INSERT_DIALOG_WIDGET_T);

    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "bin/resources/insert_window.glade", NULL);

    dialog->widgets->dialog = GTK_WIDGET(gtk_builder_get_object(builder, "insert_window"));
    dialog->widgets->txt_name = GTK_WIDGET(gtk_builder_get_object(builder, "txt_name"));
    dialog->widgets->txt_address = GTK_WIDGET(gtk_builder_get_object(builder, "txt_address"));
    dialog->widgets->txt_age = GTK_WIDGET(gtk_builder_get_object(builder, "txt_age"));
    dialog->widgets->bt_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "bt_cancel"));
    dialog->widgets->bt_confirm = GTK_WIDGET(gtk_builder_get_object(builder, "bt_confirm"));

    gtk_builder_connect_signals(builder, dialog);

    g_object_unref(builder);

    return true;
}

void on_insert_window_destroy(void)
{
}

void on_bt_insert_confirm_clicked(GtkButton *bt_confirm, void *data)
{
    // INSERT_DIALOG_T *dialog = (INSERT_DIALOG_T *)data;
    printf("confirm\n");
}

void on_bt_insert_cancel_clicked(GtkButton *bt_cancel, void *data)
{
    printf("--- cancel ----\n");

    INSERT_DIALOG_T *dialog = (INSERT_DIALOG_T *)data;
    gtk_widget_destroy(GTK_WIDGET(dialog->widgets->dialog));
}
