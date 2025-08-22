#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_register.h"
#include "repository.h"
#include "repository_factory.h"

int main(void)
{
    int option;

    REPOSITORY_BASE *repository = repopository_create("file");
    if (repository == NULL)
        return EXIT_FAILURE;

    while (true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option, repository);
    }

    free(repository);

    return EXIT_SUCCESS;
}
