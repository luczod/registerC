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
        dialog->con = args->con;
        dialog->id = args->id;
        dialog->name = args->name;
        dialog->address = args->address;
        dialog->age = args->age;

        status = edit_dialog_graphics_init(dialog);
    }

    return status;
}

bool edit_dialog_run(EDIT_DIALOG_T *dialog)
{
    bool status = false;

    if (dialog != NULL)
    {
        char buff[5] = {0};

        gtk_entry_set_text(GTK_ENTRY(dialog->widgets->txt_name), dialog->name);
        gtk_entry_set_text(GTK_ENTRY(dialog->widgets->txt_address), dialog->address);
        snprintf(buff, 5, "%d", dialog->age);
        gtk_entry_set_text(GTK_ENTRY(dialog->widgets->txt_age), buff);

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

    gtk_builder_add_from_file(builder, "resources/edit_window.glade", NULL);

    dialog->widgets->dialog = GTK_WIDGET(gtk_builder_get_object(builder, "edit_window"));
    dialog->widgets->txt_name = GTK_ENTRY(gtk_builder_get_object(builder, "txt_name"));
    dialog->widgets->txt_address = GTK_ENTRY(gtk_builder_get_object(builder, "txt_address"));
    dialog->widgets->txt_age = GTK_ENTRY(gtk_builder_get_object(builder, "txt_age"));
    dialog->widgets->bt_cancel = GTK_BUTTON(gtk_builder_get_object(builder, "bt_cancel"));
    dialog->widgets->bt_confirm = GTK_BUTTON(gtk_builder_get_object(builder, "bt_confirm"));

    gtk_builder_connect_signals(builder, dialog);

    g_object_unref(builder);

    return true;
}

void on_edit_window_destroy(void)
{
}

void on_bt_edit_confirm_clicked(GtkButton *bt_confirm, void *data)
{
    EDIT_DIALOG_T *edit = (EDIT_DIALOG_T *)data;
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(edit->widgets->txt_name));
    char *address = (char *)gtk_entry_get_text(GTK_ENTRY(edit->widgets->txt_address));
    char *age = (char *)gtk_entry_get_text(GTK_ENTRY(edit->widgets->txt_age));

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(edit->widgets->dialog),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_OK_CANCEL,
                                               "%s",
                                               "This content is about to be modify");

    int answer = gtk_dialog_run(GTK_DIALOG(dialog));
    if (answer == GTK_RESPONSE_OK)
        edit->con->on_update(edit->con->object, edit->id, name, address, age);

    gtk_widget_destroy(GTK_WIDGET(dialog));
    gtk_widget_destroy(GTK_WIDGET(edit->widgets->dialog));
}

void on_bt_edit_cancel_clicked(GtkButton *bt_cancel, void *data)
{
    printf("--- cancel ----\n");

    EDIT_DIALOG_T *dialog = (EDIT_DIALOG_T *)data;

    gtk_widget_destroy(GTK_WIDGET(dialog->widgets->dialog));
}
