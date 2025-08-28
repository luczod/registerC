#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gtk_view.h"

bool gtk_view_init(GTK_VIEW_T *view)
{
    bool status = false;

    if (view != NULL)
    {
        memset(view, 0, sizeof(GTK_VIEW_T));
        status = main_window_init(&view->main);
    }

    return status;
}

bool gtk_view_open(GTK_VIEW_T *view, GTK_VIEW_ARGS_T *args)
{
    bool status = false;
    MAIN_WINDOW_ARGS_T main_args;

    if (view != NULL && args != NULL)
    {
        main_args.argc = args->argc;
        main_args.argv = args->argv;

        status = main_window_open(&view->main, &main_args);
    }

    return status;
}

bool gtk_view_run(GTK_VIEW_T *view)
{
    bool status = false;
    if (view != NULL)
    {

        status = main_window_run(&view->main);
    }

    return status;
}

bool gtk_view_close(GTK_VIEW_T *view)
{
    bool status = false;

    if (view != NULL)
    {
        main_window_close(&view->main);
        memset(view, 0, sizeof(GTK_VIEW_T));
        status = true;
    }

    return status;
}
