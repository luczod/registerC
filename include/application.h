#ifndef APPLICATION_H
#define APPLICATION_H

#include "repository.h"
#include "view_base.h"

typedef struct APPLICATION_T
{
    VIEW_BASE *view;
    REPOSITORY_BASE *repository;
} APPLICATION_T;

bool application_init(APPLICATION_T *app, VIEW_BASE *view, REPOSITORY_BASE *repository);
bool application_run(APPLICATION_T *app);

#endif /* APPLICATION_H */