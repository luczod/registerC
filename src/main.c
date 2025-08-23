#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_register.h"
#include "repository_factory.h"

#define REPOSITORY_TYPE "sqlite"

int main(void)
{
    int option;

    // REPOSITORY_BASE *repository = repopository_create("file");
    REPOSITORY_BASE *repository = repopository_create(REPOSITORY_TYPE);
    if (repository == NULL)
        return EXIT_FAILURE;

    while (true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option, repository);
    }

    // free(repository);
    repository_destroy(REPOSITORY_TYPE, repository);

    return EXIT_SUCCESS;
}
