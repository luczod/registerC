#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_window.h"
#include <gtk/gtk.h>
#include <gtk/gtktypes.h>
#include <gtk/gtkwidget.h>

static bool main_window_graphic_init(MAIN_WINDOW_T *window);

bool main_window_init(MAIN_WINDOW_T *window)
{
    bool status = false;

    if (window != NULL)
    {
        memset(window, 0, sizeof(MAIN_WINDOW_T));
        status = true;
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

    gtk_builder_add_from_file(builder, "bin/resources/window.glade", &err);

    if (err)
    {
        g_printerr("Error loading UI: %s\n", err->message);
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

    gtk_builder_connect_signals(builder, window);

    g_object_unref(builder);

    return true;
}

void on_bt_insert_clicked(GtkButton *bt_insert, void *data)
{
    printf("insert\n");
}

void on_bt_edit_clicked(GtkButton *bt_edit, void *data)
{
    printf("edit\n");
}

void on_bt_delete_clicked(GtkButton *bt_delete, void *data)
{
    printf("delete\n");
}

void on_window_main_destroy(void)
{
    gtk_main_quit();
}
