#ifndef USE_CASE_H
#define USE_CASE_H

#include "repository.h"

void use_case_person_add(REPOSITORY_BASE *repository);
void use_case_person_delete(REPOSITORY_BASE *repository);
void use_case_person_update(REPOSITORY_BASE *repository);
void use_case_person_list(REPOSITORY_BASE *repository);
void use_case_person_find(REPOSITORY_BASE *repository);
void use_case_person_quit(REPOSITORY_BASE *repository);

#endif