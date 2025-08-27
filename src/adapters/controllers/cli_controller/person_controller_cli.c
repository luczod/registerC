#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "person_controller_cli.h"

typedef enum PERSON_CONTROLLER_OPTIONS
{
    person_add = 1,
    person_remove,
    person_update,
    person_find,
    person_getall,
    person_quit,
} PERSON_CONTROLLER_OPTIONS;

CLI_OPTION_T options_list[] =
    {
        {.index = person_add, .text = "Add Person"},
        {.index = person_remove, .text = "Remove Person"},
        {.index = person_update, .text = "Update Person"},
        {.index = person_find, .text = "Find Person"},
        {.index = person_getall, .text = "Get All Person"},
};

static void *person_controller_cli_on_selected(uint8_t index, void *data);

static bool person_controller_cli_add(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_remove(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_update(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_find(PERSON_CONTROLLER_CLI_T *cli_controller);
static bool person_controller_cli_getall(PERSON_CONTROLLER_CLI_T *cli_controller);
static void person_controller_cli_print(PERSON_CONTROLLER_CLI_T *cli_controller, const PERSON_T *person_list, unsigned int amount);

bool person_controller_cli_init(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)object;

        memset(cli_controller, 0, sizeof(PERSON_CONTROLLER_CLI_T));

        cli_controller->base.object = cli_controller;

        cli_controller->base.init = person_controller_cli_init;
        cli_controller->base.open = person_controller_cli_open;
        cli_controller->base.run = person_controller_cli_run;
        cli_controller->base.close = person_controller_cli_close;

        cli_init(&cli_controller->cli);

        cli_controller->cli.on_selected = person_controller_cli_on_selected;
    }
    return status;
}

bool person_controller_cli_open(void *object, PERSON_SERVICE_T *service)
{
    bool status = false;

    if (object != NULL && service != NULL)
    {
        PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)object;

        cli_controller->service = service;

        cli_open(&cli_controller->cli, options_list, sizeof(options_list) / sizeof(options_list[0]));
        status = true;
    }

    return status;
}

bool person_controller_cli_run(void *object)
{
    PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)object;

    cli_run(&cli_controller->cli, cli_controller);

    return true;
}

bool person_controller_cli_close(void *object)
{
    bool status = false;

    if (object != NULL)
    {
        PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)object;

        memset(cli_controller, 0, sizeof(PERSON_CONTROLLER_CLI_T));

        status = true;
    }
    return status;
}

PERSON_CONTROLLER_BASE_T person_controller_cli_create(PERSON_SERVICE_T *service)
{
    static PERSON_CONTROLLER_CLI_T cli_controller;

    person_controller_cli_init(&cli_controller);
    person_controller_cli_open(&cli_controller, service);

    return cli_controller.base;
}

static void *person_controller_cli_on_selected(uint8_t index, void *data)
{
    PERSON_CONTROLLER_CLI_T *cli_controller = (PERSON_CONTROLLER_CLI_T *)data;

    switch (index)
    {
    case person_add:
        person_controller_cli_add(cli_controller);
        break;
    case person_remove:
        person_controller_cli_remove(cli_controller);
        break;
    case person_update:
        person_controller_cli_update(cli_controller);
        break;
    case person_find:
        person_controller_cli_find(cli_controller);
        break;
    case person_getall:
        person_controller_cli_getall(cli_controller);
        break;

    default:
        break;
    }

    return NULL;
}

static bool person_controller_cli_add(PERSON_CONTROLLER_CLI_T *cli_controller)
{
    char name[PERSON_NAME_LEN] = "";
    char address[PERSON_ADDRESS_LEN] = "";
    int age;

    printf("Enter a Name: ");
    fgets(name, PERSON_NAME_LEN, stdin);
    name[strlen(name) - 1] = 0;

    printf("Enter a Address: ");
    fgets(address, PERSON_ADDRESS_LEN, stdin);
    address[strlen(address) - 1] = 0;

    printf("Enter an Age: ");
    scanf("%d", &age);
    getchar();

    PERSON_T person = person_create(name, address, age);
    cli_controller->service->base.add(cli_controller->service->base.object, &person);

    return true;
}

static bool person_controller_cli_remove(PERSON_CONTROLLER_CLI_T *cli_controller)
{
    PERSON_T person;
    printf("Type an ID to delete: ");
    scanf("%d", &person.id);
    getchar();

    cli_controller->service->base.remove(cli_controller->service->base.object, &person);

    return true;
}

static bool person_controller_cli_update(PERSON_CONTROLLER_CLI_T *cli_controller)
{
    int id;
    char name[PERSON_NAME_LEN] = "";
    char address[PERSON_ADDRESS_LEN] = "";
    int age;

    printf("Type an ID to update: ");
    scanf("%d", &id);
    getchar();

    printf("Enter a Name: ");
    fgets(name, PERSON_NAME_LEN, stdin);
    name[strlen(name) - 1] = 0;

    printf("Enter a Address: ");
    fgets(address, PERSON_ADDRESS_LEN, stdin);
    address[strlen(address) - 1] = 0;

    printf("Enter an Age: ");
    scanf("%d", &age);
    getchar();

    PERSON_T person = person_create(name, address, age);
    person.id = id;

    cli_controller->service->base.update(cli_controller->service->base.object, &person);

    return true;
}

static bool person_controller_cli_find(PERSON_CONTROLLER_CLI_T *cli_controller)
{
    char name[PERSON_NAME_LEN] = "";
    bool status = false;

    printf("Type a Name to Find: ");
    fgets(name, PERSON_NAME_LEN, stdin);
    name[strlen(name) - 1] = 0;

    PERSON_T person = person_create(name, NULL, 0);

    status = cli_controller->service->base.find(cli_controller->service->base.object, &person);

    if (status == true)
    {
        printf("Found: ");
        person_controller_cli_print(cli_controller, &person, 1);
    }
    else
    {
        printf("Not Found.\n");
    }

    return status;
}

static bool person_controller_cli_getall(PERSON_CONTROLLER_CLI_T *cli_controller)
{
    PERSON_T *person_list = NULL;
    unsigned int amount = 0;

    cli_controller->service->base.getall(cli_controller->service->base.object, &person_list, &amount);

    person_controller_cli_print(cli_controller, person_list, amount);

    free(person_list);
    return true;
}

static void person_controller_cli_print(PERSON_CONTROLLER_CLI_T *cli_controller, const PERSON_T *person_list, unsigned int amount)
{
    (void)cli_controller;

    for (unsigned int i = 0; i < amount; i++)
    {
        PERSON_T *person = (PERSON_T *)&person_list[i];

        printf("ID: %d, Name: %s, Address: %s, Age: %d\n", person->id, person->name, person->address, person->age);
    }
}
