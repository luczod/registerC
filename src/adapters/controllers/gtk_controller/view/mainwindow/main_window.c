#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtktypes.h>
#include <gtk/gtkwidget.h>
#include "main_window.h"

typedef enum HEARDER_T
{
    PERSON_ID,
    PERSON_NAME,
    PERSON_ADDRESS,
    PERSON_AGE,
} HEARDER_T;

static bool main_window_graphic_init(MAIN_WINDOW_T *window);
static void main_window_set_all_persons(void *object, PERSON_T *list, unsigned int amount);
static int main_window_show_dialog_message(void *object, const char *list, MESSAGE_TYPE_T type, DIALOG_BUTTON_T button_type);
static GtkMessageType main_window_get_type(MESSAGE_TYPE_T type);
static void main_window_model_reload(MAIN_WINDOW_T *mw);

bool main_window_init(MAIN_WINDOW_T *window)
{
    bool status = false;

    if (window != NULL)
    {
        memset(window, 0, sizeof(MAIN_WINDOW_T));
        window->base.object = window;
        window->base.set_all_persons = main_window_set_all_persons;
        window->base.show_dialog_message = main_window_show_dialog_message;

        if (insert_dialog_init(&window->insert) == true && edit_dialog_init(&window->edit) == true)
        {
            status = true;
        }
    }

    return status;
}

bool main_window_open(MAIN_WINDOW_T *window, MAIN_WINDOW_ARGS_T *args)
{
    bool status = false;

    if (window != NULL && args != NULL)
    {
        window->argc = args->argc;
        window->argv = args->argv;
        window->con = args->con;

        status = main_window_graphic_init(window);
    }

    return status;
}

bool main_window_run(MAIN_WINDOW_T *window)
{
    bool status = false;

    if (window != NULL)
    {
        gtk_widget_show(window->widgets->window);
        gtk_main();
        status = true;
    }

    return status;
}

bool main_window_close(MAIN_WINDOW_T *window)
{
    bool status = false;

    if (window != NULL)
    {
        g_slice_free(MAIN_WINDOW_WIDGETS_T, window->widgets);
        memset(window, 0, sizeof(MAIN_WINDOW_T));
        status = true;
    }

    return status;
}

static bool main_window_graphic_init(MAIN_WINDOW_T *window)
{
    GtkBuilder *builder;
    GError *err = NULL;

    window->widgets = g_slice_new(MAIN_WINDOW_WIDGETS_T);

    gtk_init(&window->argc, &window->argv);
    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "resources/window.glade", &err);

    if (err)
    {
        g_printerr("Error loading UI main: %s\n", err->message);
        g_error_free(err);

        exit(EXIT_FAILURE);
    }

    window->widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    window->widgets->person_treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "person_treeview"));
    window->widgets->person_model = GTK_TREE_MODEL(gtk_builder_get_object(builder, "person_model"));

    window->widgets->input_search = GTK_ENTRY(gtk_builder_get_object(builder, "input_search"));
    window->widgets->bt_insert = GTK_BUTTON(gtk_builder_get_object(builder, "bt_insert"));
    window->widgets->bt_delete = GTK_BUTTON(gtk_builder_get_object(builder, "bt_delete"));
    window->widgets->bt_edit = GTK_BUTTON(gtk_builder_get_object(builder, "bt_edit"));
    window->widgets->bt_find = GTK_BUTTON(gtk_builder_get_object(builder, "bt_find"));

    gtk_builder_connect_signals(builder, window);

    g_object_unref(builder);

    return true;
}

void on_bt_insert_clicked(GtkButton *bt_insert, void *data)
{
    printf("------ insert------\n");
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)data;

    INSERT_DIALOG_ARGS_T args = {
        .argc = mw->argc,
        .argv = mw->argv,
        .parent = mw->widgets->window,
        .con = mw->con,
    };

    insert_dialog_open(&mw->insert, &args);
    insert_dialog_run(&mw->insert);
    insert_dialog_close(&mw->insert);

    main_window_model_reload(mw);
}

void on_bt_edit_clicked(GtkButton *bt_edit, void *data)
{
    printf("------ edit------\n");

    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)data;

    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;

    GValue value_id = {
        0,
    };
    GValue value_name = {
        0,
    };
    GValue value_address = {
        0,
    };
    GValue value_age = {
        0,
    };

    selection = gtk_tree_view_get_selection(mw->widgets->person_treeview);
    gboolean status = gtk_tree_selection_get_selected(selection, &model, &iter);

    if (status == TRUE)
    {
        gtk_tree_model_get_value(model, &iter, PERSON_ID, &value_id);
        int id = g_value_get_int(&value_id);

        gtk_tree_model_get_value(model, &iter, PERSON_NAME, &value_name);
        char *name = (char *)g_value_get_string(&value_name);

        gtk_tree_model_get_value(model, &iter, PERSON_ADDRESS, &value_address);
        char *address = (char *)g_value_get_string(&value_address);

        gtk_tree_model_get_value(model, &iter, PERSON_AGE, &value_age);
        int age = g_value_get_int(&value_age);

        EDIT_DIALOG_ARGS_T args = {
            .argc = mw->argc,
            .argv = mw->argv,
            .parent = mw->widgets->window,
            .con = mw->con,
            .id = id,
            .name = name,
            .address = address,
            .age = age,
        };

        edit_dialog_open(&mw->edit, &args);
        edit_dialog_run(&mw->edit);
        edit_dialog_close(&mw->edit);

        main_window_model_reload(mw);

        g_value_unset(&value_id);
        g_value_unset(&value_name);
        g_value_unset(&value_address);
        g_value_unset(&value_age);
    }
}

void on_bt_delete_clicked(GtkButton *bt_delete, void *data)
{
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)data;
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    int id;

    GValue value = {
        0,
    };

    selection = gtk_tree_view_get_selection(mw->widgets->person_treeview);
    gboolean status = gtk_tree_selection_get_selected(selection, &model, &iter);

    if (status == TRUE)
    {
        int answer = main_window_show_dialog_message(mw, "This register is about to be deleted. Are you sure?", MESSAGE_QUESTION, DIALOG_BUTTON_OK_CANCEL);
        if (answer == GTK_RESPONSE_OK)
        {
            gtk_tree_model_get_value(model, &iter, PERSON_ID, &value);
            id = g_value_get_int(&value);
            mw->con->on_delete(mw->con->object, id);

            main_window_model_reload(mw);
        }
    }

    g_value_unset(&value);
}

void on_bt_find_clicked(GtkButton *bt_find, void *data)
{
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)data;
    const char *text = (const char *)gtk_entry_get_text(GTK_ENTRY(mw->widgets->input_search));

    mw->con->on_search(mw->con->object, text);
}

void on_window_main_destroy(void)
{
    gtk_main_quit();
}

void on_window_main_show(GtkWidget *object, void *data)
{
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)data;
    mw->con->on_get(mw->con->object);
}

void main_window_set_all_persons(void *object, PERSON_T *list, unsigned int amount)
{
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)object;

    for (unsigned int i = 0; i < amount; i++)
    {
        GtkTreeIter iter;
        PERSON_T *p = &list[i];

        gtk_list_store_append(GTK_LIST_STORE(mw->widgets->person_model), &iter);

        gtk_list_store_set(GTK_LIST_STORE(mw->widgets->person_model), &iter,
                           PERSON_ID, p->id,
                           PERSON_NAME, p->name,
                           PERSON_ADDRESS, p->address,
                           PERSON_AGE, p->age,
                           -1);
    }
}

static int main_window_show_dialog_message(void *object, const char *message, MESSAGE_TYPE_T type, DIALOG_BUTTON_T button_type)
{
    MAIN_WINDOW_T *mw = (MAIN_WINDOW_T *)object;
    int answer;

    GtkWidget *d = gtk_message_dialog_new(GTK_WINDOW(mw->widgets->window),
                                          GTK_DIALOG_MODAL,
                                          main_window_get_type(type),
                                          button_type,
                                          "%s",
                                          message);

    answer = gtk_dialog_run(GTK_DIALOG(d));
    gtk_widget_destroy(d);

    return answer;
}

static GtkMessageType main_window_get_type(MESSAGE_TYPE_T type)
{
    GtkMessageType internal_type = GTK_MESSAGE_INFO;

    switch (type)
    {
    case MESSAGE_INFO:
        internal_type = GTK_MESSAGE_INFO;
        break;
    case MESSAGE_WARNING:
        internal_type = GTK_MESSAGE_WARNING;
        break;
    case MESSAGE_ERROR:
        internal_type = GTK_MESSAGE_ERROR;
        break;
    case MESSAGE_QUESTION:
        internal_type = GTK_MESSAGE_QUESTION;
        break;

    default:
        break;
    }

    return internal_type;
}

void main_window_model_reload(MAIN_WINDOW_T *mw)
{
    gtk_list_store_clear(GTK_LIST_STORE(mw->widgets->person_model));
    mw->con->on_get(mw->con->object);
}
