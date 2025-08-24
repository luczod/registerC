#include <stdlib.h>
#include <stdio.h>
#include "cli.h"
#include "menu_register.h"

static bool cli_view_init(void *object);
static bool cli_view_exec(void *object, REPOSITORY_BASE *repository);

VIEW_BASE *cli_view_create(void)
{
    VIEW_BASE *view = (VIEW_BASE *)malloc(sizeof(VIEW_BASE));

    if (view)
    {
        view->object = NULL;
        view->init = cli_view_init;
        view->exec = cli_view_exec;
    }

    return view;
}

bool cli_view_destroy(VIEW_BASE *view)
{
    bool status = false;

    if (view)
    {
        free(view);
        status = true;
    }

    return status;
}

static bool cli_view_init(void *object)
{
    (void)object;
    return true;
}

static bool cli_view_exec(void *object, REPOSITORY_BASE *repository)
{
    int option;

    while (true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option, repository);
    }

    return true;
}
