#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "sqlite_database.h"

typedef struct SQLITE_CONTEXT
{
    const char *database_name;
    sqlite3 *db_connection;
} SQLITE_CONTEXT;

static bool sqlite_store(void *object, STORE_ACTION_T *action);
static bool sqlite_recovery_list(void *object, PERSON_T **person_list, int *items_amount);

REPOSITORY_BASE *sqlite_create_database(void)
{
    REPOSITORY_BASE *repository = (REPOSITORY_BASE *)malloc(sizeof(REPOSITORY_BASE));

    if (repository)
    {
        SQLITE_CONTEXT *ctx = (SQLITE_CONTEXT *)malloc(sizeof(REPOSITORY_BASE));

        if (ctx)
        {
            ctx->database_name = "person_database.db";
            repository->object = ctx;
            repository->store = sqlite_store;
            repository->recovery_list = sqlite_recovery_list;
        }
        else
        {
            free(repository);
            repository = NULL;
        }
    }

    return repository;
}

static bool sqlite_store(void *object, STORE_ACTION_T *action)
{
    return false;
}

static bool sqlite_recovery_list(void *object, PERSON_T **person_list, int *items_amount)
{
    return false;
}