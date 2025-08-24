#ifndef CLI_H
#define CLI_H

#include "view_base.h"

VIEW_BASE *cli_view_create(void);
bool cli_view_destroy(VIEW_BASE *view);

#endif /* CLI_H */