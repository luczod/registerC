#ifndef VIEW_BASE_H
#define VIEW_BASE_H

#include "repository.h"

typedef struct VIEW_BASE
{
    void *object;
    bool (*init)(void *object);
    bool (*exec)(void *object, REPOSITORY_BASE *repository);
} VIEW_BASE;

#endif /* VIEW_BASE_H */