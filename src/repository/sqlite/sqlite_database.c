#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include "sqlite_database.h"

typedef struct SQLITE_CONTEXT
{
    const char *database_name;
    sqlite3 *db_connection;
} SQLITE_CONTEXT;

typedef struct SQLITE_PERSON_T
{
    PERSON_T *list;
    int amount;
} SQLITE_PERSON_T;

static bool sqlite_database_open(SQLITE_CONTEXT *ctx);
static bool sqlite_prepare_table(SQLITE_CONTEXT *ctx);

static bool sqlite_insert(SQLITE_CONTEXT *ctx, const PERSON_T *person);
static bool sqlite_update(SQLITE_CONTEXT *ctx, const PERSON_T *person);
static bool sqlite_delete(SQLITE_CONTEXT *ctx, const PERSON_T *person);

static bool sqlite_store(void *object, STORE_ACTION_T *store);
static bool sqlite_recovery_list(void *object, PERSON_T **person_list, int *items_amount);

static int select_callback(void *user_data, int columns, char **colums_data, char **colums_name);
static int sqlite_get_items_amount(SQLITE_CONTEXT *ctx);

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

static int select_callback(void *user_data, int columns, char **columns_data, char **columns_name)
{

    SQLITE_PERSON_T *person = (SQLITE_PERSON_T *)user_data;

    person->list[person->amount].id = atoi(columns_data[id_pos]);
    strncpy(person->list[person->amount].name, columns_data[name_pos], PERSON_NAME_LEN);
    strncpy(person->list[person->amount].address, columns_data[address_pos], PERSON_ADDRESS_LEN);
    person->list[person->amount].age = atoi(columns_data[age_pos]);

    person->amount++;

    return 0;
}

bool sqlite_destroy_database(REPOSITORY_BASE *repository)
{
    bool status = false;

    if (repository)
    {
        SQLITE_CONTEXT *ctx = (SQLITE_CONTEXT *)repository->object;
        sqlite3_close(ctx->db_connection);

        free(repository->object);
        free(repository);

        status = true;
    }

    return status;
}

static bool sqlite_store(void *object, STORE_ACTION_T *store)
{
    bool state = false;
    SQLITE_CONTEXT *ctx = (SQLITE_CONTEXT *)object;

    sqlite_prepare_table(object);

    switch (store->action)
    {
    case repo_insert:
        state = sqlite_insert(ctx, store->person);
        break;
    case repo_delete:
        state = sqlite_delete(ctx, &store->person[store->id]);
        break;
    case repo_update:
        state = sqlite_update(ctx, &store->person[store->id]);
        break;
    default:
        break;
    }

    return state;
}

static bool sqlite_recovery_list(void *object, PERSON_T **person_list, int *items_amount)
{
    int ret;
    bool status = false;
    char *error_msg;

    SQLITE_CONTEXT *ctx = (SQLITE_CONTEXT *)object;

    char *query = "SELECT * FROM PERSON_TB;";

    SQLITE_PERSON_T sql_person = {
        .amount = 0,
    };

    sqlite_prepare_table(ctx);

    do
    {
        *items_amount = sqlite_get_items_amount(ctx);
        if (*items_amount <= 0)
            break;

        sql_person.list = (PERSON_T *)malloc(sizeof(PERSON_T) * (*items_amount));
        if (sql_person.list == NULL)
            break;

        sqlite_database_open(ctx);

        ret = sqlite3_exec(ctx->db_connection, query, select_callback, &sql_person, &error_msg);
        if (ret != SQLITE_OK)
        {
            fprintf(stderr, "SQL list error: %s\n", error_msg);
            sqlite3_free(error_msg);
            break;
        }

        *person_list = sql_person.list;

    } while (false);

    sqlite3_close(ctx->db_connection);

    return status;
}

static bool sqlite_database_open(SQLITE_CONTEXT *ctx)
{
    bool status = true;

    int ret = sqlite3_open(ctx->database_name, &ctx->db_connection);

    if (ret)
    {
        fprintf(stderr, "It was not possible to open database %s\n", ctx->database_name);
        status = false;
    }
    return status;
}

static bool sqlite_prepare_table(SQLITE_CONTEXT *ctx)
{
    bool status = true;
    int ret;
    char *error_msg;

    char *sql = "CREATE TABLE IF NOT EXISTS PERSON_TB("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "NAME TEXT NOT NULL,"
                "ADDRESS TEXT NOT NULL,"
                "AGE INTEGER NOT NULL);";

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->db_connection, sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL prepare error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->db_connection);
    return status;
}

static bool sqlite_insert(SQLITE_CONTEXT *ctx, const PERSON_T *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "INSERT INTO PERSON_TB(NAME, ADDRESS, AGE) VALUES('%s','%s','%d');";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->db_connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL insert error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->db_connection);

    return status;
}

static bool sqlite_update(SQLITE_CONTEXT *ctx, const PERSON_T *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "UPDATE PERSON_TB SET NAME = '%s', ADDRESS = '%s', AGE = '%d' WHERE ID = '%d';";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age, person->id);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->db_connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL update error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->db_connection);

    return status;
}

static bool sqlite_delete(SQLITE_CONTEXT *ctx, const PERSON_T *person)
{
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "DELETE PERSON_TB WHERE ID = '%d';";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->id);

    sqlite_database_open(ctx);

    ret = sqlite3_exec(ctx->db_connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL delete error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(ctx->db_connection);

    return status;
}

int sqlite_get_items_amount(SQLITE_CONTEXT *ctx)
{
    int rc;
    char *query;
    sqlite3_stmt *stmt;
    int row_count = -1;

    sqlite_database_open(ctx);

    query = "SELECT COUNT(*) FROM PERSON_TB;";

    do
    {
        rc = sqlite3_prepare_v2(ctx->db_connection, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK)
            break;

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_ROW)
            break;

        row_count = sqlite3_column_int(stmt, 0);
    } while (false);

    sqlite3_finalize(stmt);
    sqlite3_close(ctx->db_connection);

    return row_count;
}
