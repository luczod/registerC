#ifndef PERSON_H
#define PERSON_H

#define PERSON_NAME_LEN 120
#define PERSON_ADDRESS_LEN 120

typedef struct PERSON_T
{
    int id;
    char name[PERSON_ADDRESS_LEN];
    char address[PERSON_ADDRESS_LEN];
    int age;
} PERSON_T;

PERSON_T person_create(const char *name, const char *address, const int age);

#endif /* PERSON_H*/
