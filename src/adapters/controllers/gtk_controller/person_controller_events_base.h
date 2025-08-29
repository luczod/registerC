#ifndef PERSON_CONTROLLER_EVENTS_BASE_H
#define PERSON_CONTROLLER_EVENTS_BASE_H

typedef struct PERSON_CONTROLLER_EVENTS_BASE_T
{
    void *object;
    void (*on_get)(void *object);
    void (*on_add)(void *object, char *name, char *address, char *age);
    void (*on_update)(void *object, int id, char *name, char *address, char *age);
    void (*on_delete)(void *object, int id);
    void (*on_search)(void *object, const char *name);
} PERSON_CONTROLLER_EVENTS_BASE_T;

#endif /* PERSON_CONTROLLER_EVENTS_BASE_H */