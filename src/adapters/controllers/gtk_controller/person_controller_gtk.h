#ifndef PERSON_CONTROLLER_GTK_H
#define PERSON_CONTROLLER_GTK_H

#include "gtk_view.h"
#include "person_controller_base.h"

typedef struct PERSON_CONTROLLER_GTK_T
{
    PERSON_CONTROLLER_BASE_T base;
    PERSON_SERVICE_T *service;
    GTK_VIEW_T view;
} PERSON_CONTROLLER_GTK_T;

bool person_controller_gtk_init(void *object);
bool person_controller_gtk_open(void *object, PERSON_CONTROLLER_ARGS_T *args);
bool person_controller_gtk_run(void *object);
bool person_controller_gtk_close(void *object);

PERSON_CONTROLLER_BASE_T person_controller_gtk_create(PERSON_CONTROLLER_ARGS_T *args);

#endif /* PERSON_CONTROLLER_GTK_H */