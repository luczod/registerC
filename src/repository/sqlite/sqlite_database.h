#ifndef SQLITE_DATABASE_H
#define SQLITE_DATABASE_H

#include <stdbool.h>
#include <string.h>
#include "repository.h"

REPOSITORY_BASE *sqlite_create_database(void);

#endif /* SQLITE_DATABASE_H */