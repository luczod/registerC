#ifndef PERSON_H
#define PERSON_H

#define PERSON_NAME_LEN 120
#define PERSON_ADDRESS_LEN 120

typedef struct
{
    char name[PERSON_ADDRESS_LEN];
    char address[PERSON_ADDRESS_LEN];
    int age;
} PERSON_T;

PERSON_T person_create(void);
void person_parser(char *buffer, PERSON_T *people);
char *person_input_name(void);

#endif /* PERSON_H*/
