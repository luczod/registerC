#ifndef VIEW_BASE_H
#define VIEW_BASE_H

#include "person.h"

typedef enum MESSAGE_TYPE_T
{
    MESSAGE_INFO,
    MESSAGE_WARNING,
    MESSAGE_ERROR,
    MESSAGE_QUESTION,
} MESSAGE_TYPE_T;

typedef enum DIALOG_BUTTON_T
{
    DIALOG_BUTTON_NONE,
    DIALOG_BUTTON_OK,
    DIALOG_BUTTON_CLOSE,
    DIALOG_BUTTON_CANCEL,
    DIALOG_BUTTON_YES_NO,
    DIALOG_BUTTON_OK_CANCEL,
} DIALOG_BUTTON_T;

typedef struct VIEW_BASE_T
{
    void *object;
    void (*set_all_persons)(void *object, PERSON_T *list, unsigned int amount);
    int (*show_dialog_message)(void *object, const char *list, MESSAGE_TYPE_T type, DIALOG_BUTTON_T button_type);
} VIEW_BASE_T;

#endif /* VIEW_H */