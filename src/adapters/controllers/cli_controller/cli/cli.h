#ifndef CLI_H
#define CLI_H

#include <stdbool.h>
#include <stdint.h>

typedef void *(*cli_event_t)(uint8_t index, void *data);

typedef struct CLI_OPTION_T
{
    uint8_t index;
    char *text;
} CLI_OPTION_T;

typedef struct CLI_T
{
    CLI_OPTION_T *option_list;
    uint8_t option_amount;
    cli_event_t on_selected;
} CLI_T;

bool cli_init(CLI_T *cli);
bool cli_open(CLI_T *cli, CLI_OPTION_T *option_list, uint8_t option_amount);
bool cli_run(CLI_T *cli, void *data);

#endif /* CLI_H */