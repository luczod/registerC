#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

PERSON_T person_create(const char *name, const char *address, const int age)
{
    PERSON_T person;

    memset(&person, 0, sizeof(PERSON_T));

    if (name != NULL)
        strncpy(person.name, name, PERSON_NAME_LEN);

    if (address != NULL)
        strncpy(person.address, address, PERSON_ADDRESS_LEN);

    person.age = age;

    return person;
}
