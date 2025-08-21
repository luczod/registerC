#include <stdio.h>
#include <stdlib.h>
#include "use_cases.h"
#include "repository.h"

void use_case_person_quit(REPOSITORY_BASE *repository)
{
    printf("Exit program ----------\n");

    (void)repository;

    exit(0);
}
