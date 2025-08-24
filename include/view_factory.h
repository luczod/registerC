#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "repository.h"
#include "view_base.h"

VIEW_BASE *view_create(const char *type);
bool view_destroy(const char *type, VIEW_BASE *view);

#endif /* VIEW_FACTORY_H */