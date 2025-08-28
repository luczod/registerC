#ifndef GTK_VIEW_H
#define GTK_VIEW_H

#include "main_window.h"

typedef struct GTK_VIEW_T
{
    MAIN_WINDOW_T main;
} GTK_VIEW_T;

typedef struct GTK_VIEW_ARGS_T
{
    MAIN_WINDOW_T main;
    int argc;
    char **argv;
} GTK_VIEW_ARGS_T;

bool gtk_view_init(GTK_VIEW_T *view);
bool gtk_view_open(GTK_VIEW_T *view, GTK_VIEW_ARGS_T *args);
bool gtk_view_run(GTK_VIEW_T *view);
bool gtk_view_close(GTK_VIEW_T *view);

#endif /* GTK_VIEW_H */