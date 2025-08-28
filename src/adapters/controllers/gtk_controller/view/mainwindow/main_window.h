
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <stdbool.h>

typedef struct MAIN_WINDOW_WIDGETS_T
{
    void *window;
} MAIN_WINDOW_WIDGETS_T;

typedef struct MAIN_WINDOW_T
{
    MAIN_WINDOW_WIDGETS_T *widgets;
    int argc;
    char **argv;
} MAIN_WINDOW_T;

typedef struct MAIN_WINDOW_ARGS_T
{
    int argc;
    char **argv;
} MAIN_WINDOW_ARGS_T;

bool main_window_init(MAIN_WINDOW_T *window);
bool main_window_open(MAIN_WINDOW_T *window, MAIN_WINDOW_ARGS_T *args);
bool main_window_run(MAIN_WINDOW_T *window);
bool main_window_close(MAIN_WINDOW_T *window);

#endif /* MAIN_WINDOW_H */
