#ifndef REPOSITORY_FACTORY_H
#define REPOSITORY_FACTORY_H

#include "repository.h"

REPOSITORY_BASE *repopository_create(const char *type);
bool repository_destroy(const char *type, REPOSITORY_BASE *repository);

#endif /* REPOSITORY_FACTORY_H*/