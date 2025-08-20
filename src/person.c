#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

PERSON_T person_create(void)
{
    PERSON_T person;

    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name) - 1] = 0;

    printf("Type a address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address) - 1] = 0;

    printf("Type a age: ");
    scanf("%d", &person.age);
    getchar();

    return person;
}

char *person_input_name(void)
{
    char *name = calloc(1, PERSON_NAME_LEN + 1);
    printf("Type a name to find: ");
    fgets(name, PERSON_NAME_LEN - 1, stdin);
    // remove the trailing newline by overwriting the last character with '\0'.
    name[strlen(name) - 1] = 0;

    return name;
}

void person_parser(char *buffer, PERSON_T *person)
{
    if (buffer == NULL || person == NULL)
        return;

    char *data = strtok(buffer, ",");
    strncpy(person->name, data, PERSON_NAME_LEN);

    data = strtok(NULL, ",");
    strncpy(person->address, data, PERSON_ADDRESS_LEN);

    data = strtok(NULL, ",");
    person->age = atoi(data);
}