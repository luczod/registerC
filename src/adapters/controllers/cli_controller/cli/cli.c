#include <stdlib.h>
#include <stdio.h>
#include "cli.h"

static void cli_print_menu(CLI_T *cli);
static uint8_t cli_get_option(CLI_T *cli);
static void cli_option_exec(CLI_T *cli, uint8_t choose, void *data);

bool cli_init(CLI_T *cli)
{
    bool status = false;

    if (cli != NULL)
    {
        memset(cli, 0, sizeof(CLI_T));
        status = true;
    }
    return status;
}

bool cli_open(CLI_T *cli, CLI_OPTION_T *option_list, uint8_t option_amount)
{
    bool status = false;

    if (cli != NULL)
    {
        cli->option_list = option_list;
        cli->option_amount = option_amount;
        status = true;
    }

    return status;
}

bool cli_run(CLI_T *cli, void *data)
{
    bool status = false;
    uint8_t choose;

    do
    {
        cli_print_menu(cli);
        choose = cli_get_option(cli);
        cli_option_exec(cli, choose, data);
    } while (choose != 0);

    return status;
}

static void cli_print_menu(CLI_T *cli)
{
    for (uint8_t i = 0; i < cli->option_amount; i++)
    {
        CLI_OPTION_T *option = &cli->option_list[i];
        fprint(stdout, "%d, %s\n", option->index, option->text);
    }

    fprint(stdout, "0. Quit\n");
}

static uint8_t cli_get_option(CLI_T *cli)
{
    (void)cli;
    int choose;

    fprintf(stdout, "Select an option: ");
    scanf("%d", &choose);
    getchar();
    putchar('\n');

    return (uint8_t)choose;
}

static void cli_option_exec(CLI_T *cli, uint8_t choose, void *data)
{
    uint8_t i;

    for (i = 0; i < cli->option_amount; i++)
    {
        CLI_OPTION_T *option = &cli->option_list[i];

        if (choose == option->index)
        {
            cli->on_selected(option->index, data);
            break;
        }
    }

    if (i == cli->option_amount)
    {
        printf("This option is not available.");
    }

    printf("\n\n");
}
