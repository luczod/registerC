#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "view_base.h"
#include "cli/cli.h"

typedef struct VIEW_T
{
    const char *name;
    VIEW_BASE *(*view_create)(void);
    bool (*view_destroy)(VIEW_BASE *view);
} VIEW_T;

VIEW_T views[] =
    {
        {
            .name = "cli",
            .view_create = cli_view_create,
            .view_destroy = cli_view_destroy,
        },
};

static const unsigned int view_amount = sizeof(views) / sizeof(views[0]);

VIEW_BASE *view_create(const char *type)
{
    VIEW_BASE *view = NULL;

    for (int i = 0; i < view_amount; i++)
    {
        if (strncmp(views[i].name, type, strlen(views[i].name)) == 0)
        {
            view = views[i].view_create();
            break;
        }
    }

    return view;
}

bool view_destroy(const char *type, VIEW_BASE *view)
{
    bool status = false;

    if (view != NULL)
    {
        for (int i = 0; i < view_amount; i++)
        {
            if (strncmp(views[i].name, type, strlen(views[i].name)) == 0)
            {
                status = views[i].view_destroy(view);
                break;
            }
        }
    }

    return status;
}
