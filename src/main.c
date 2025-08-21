#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_register.h"
#include "repository.h"

int main(void)
{
    int option;

    while (true)
    {
        print_menu();
        scanf("%d", &option);
        getchar();
        option_select(option);
    }

    return EXIT_SUCCESS;
}
