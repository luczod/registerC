#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdio.h>
#include "person_repository_sqlite.h"
#include "person_repository_factory.h"

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

static int select_callback(void *user_data, int columns, char **columns_data, char **columns_name);

static bool person_repository_sqlite_add(void *object, PERSON_T *person);
static bool person_repository_sqlite_remove(void *object, PERSON_T *person);
static bool person_repository_sqlite_update(void *object, PERSON_T *person);
static bool person_repository_sqlite_find(void *object, PERSON_T *person);
static bool person_repository_sqlite_getall(void *object, PERSON_T **person_list, unsigned int *amount);

static bool sqlite_database_open(PERSON_REPOSITORY_SQLITE_T *sqlite);
static bool sqlite_prepare_table(PERSON_REPOSITORY_SQLITE_T *sqlite);
static int sqlite_get_items_amount(PERSON_REPOSITORY_SQLITE_T *sqlite);

PERSON_REPOSITORY_BASE_T person_repository_sqlite_create(void)
{
    static PERSON_REPOSITORY_SQLITE_T sqlite;

    person_repository_file_init(&sqlite);
    person_repository_file_open(&sqlite);

    return sqlite.base;
}

bool person_repository_sqlite_init(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    bool status = false;

    if (sqlite != NULL)
    {
        memset(sqlite, 0, sizeof(PERSON_REPOSITORY_SQLITE_T));

        sqlite->base.object = sqlite; // type

        sqlite->base.add = person_repository_sqlite_add;
        sqlite->base.remove = person_repository_sqlite_remove;
        sqlite->base.update = person_repository_sqlite_update;
        sqlite->base.find = person_repository_sqlite_find;
        sqlite->base.getall = person_repository_sqlite_getall;

        sqlite->database_name = "person_database.db";

        status = true;
    }

    return status;
}

bool person_repository_sqlite_open(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    bool status = false;
    if (sqlite != NULL)
    {
        status = true;
    }
    return status;
}

bool person_repository_sqlite_close(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    bool status = false;
    if (sqlite != NULL)
    {
        memset(sqlite, 0, sizeof(PERSON_REPOSITORY_SQLITE_T));
        status = true;
    }
    return status;
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

static bool sqlite_database_open(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    bool status = true;

    int ret = sqlite3_open(sqlite->database_name, (sqlite3 **)&sqlite->connection);

    if (ret)
    {
        fprintf(stderr, "It was not possible to open database %s\n", sqlite->database_name);
        status = false;
    }

    return status;
}

static bool sqlite_prepare_table(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    bool status = true;
    int ret;
    char *error_msg;

    char *sql = "CREATE TABLE IF NOT EXISTS PERSON_TB("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "NAME TEXT NOT NULL,"
                "ADDRESS TEXT NOT NULL,"
                "AGE INTEGER NOT NULL);";

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL prepare error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);
    return status;
}

static int sqlite_get_items_amount(PERSON_REPOSITORY_SQLITE_T *sqlite)
{
    int rc;
    char *query;
    sqlite3_stmt *stmt;
    int row_count = -1;

    sqlite_database_open(sqlite);

    query = "SELECT COUNT(*) FROM PERSON_TB;";

    do
    {
        rc = sqlite3_prepare_v2(sqlite->connection, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK)
            break;

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_ROW)
            break;

        row_count = sqlite3_column_int(stmt, 0);
    } while (false);

    sqlite3_finalize(stmt);
    sqlite3_close(sqlite->connection);

    return row_count;
}

static bool person_repository_sqlite_add(void *object, PERSON_T *person)
{
    PERSON_REPOSITORY_SQLITE_T *sqlite = (PERSON_REPOSITORY_SQLITE_T *)object;
    bool status = true;
    int ret;
    char *error_msg;
    char *query = "INSERT INTO PERSON_TB(NAME, ADDRESS, AGE) VALUES('%s','%s','%d');";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL insert error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_remove(void *object, PERSON_T *person)
{
    PERSON_REPOSITORY_SQLITE_T *sqlite = (PERSON_REPOSITORY_SQLITE_T *)object;

    bool status = true;
    int ret;
    char *error_msg;
    char *query = "DELETE PERSON_TB WHERE ID = '%d';";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->id);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL delete error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_update(void *object, PERSON_T *person)
{
    PERSON_REPOSITORY_SQLITE_T *sqlite = (PERSON_REPOSITORY_SQLITE_T *)object;

    bool status = true;
    int ret;
    char *error_msg;
    char *query = "UPDATE PERSON_TB SET NAME = '%s', ADDRESS = '%s', AGE = '%d' WHERE ID = '%d';";
    char buffer_sql[SQLITE_BUFFER_SIZE] = {0};

    snprintf(buffer_sql, SQLITE_BUFFER_SIZE, query, person->name, person->address, person->age, person->id);

    sqlite_database_open(sqlite);

    ret = sqlite3_exec(sqlite->connection, buffer_sql, NULL, 0, &error_msg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "SQL update error: %s\n", error_msg);
        sqlite3_free(error_msg);
        status = false;
    }

    sqlite3_close(sqlite->connection);

    return status;
}

static bool person_repository_sqlite_find(void *object, PERSON_T *person)
{
    PERSON_REPOSITORY_SQLITE_T *sqlite = (PERSON_REPOSITORY_SQLITE_T *)object;
    bool status = false;

    PERSON_T *person_list = NULL;
    unsigned int amount = 0;

    status = person_repository_sqlite_getall(sqlite, &person_list, &amount);

    if (status == true)
    {
        status = false;

        for (unsigned int i = 0; i < amount; i++)
        {
            char *found = strstr(person_list[i].name, person->name);
            if (found != NULL)
            {
                memcpy(person, &person_list[i], sizeof(PERSON_T));
                status = true;
                break;
            }
        }

        free(person_list);
    }

    return status;
}

static bool person_repository_sqlite_getall(void *object, PERSON_T **person_list, unsigned int *amount)
{
    int ret;
    bool status = false;
    char *error_msg;

    PERSON_REPOSITORY_SQLITE_T *sqlite = (PERSON_REPOSITORY_SQLITE_T *)object;

    char *query = "SELECT * FROM PERSON_TB;";

    SQLITE_PERSON_T sql_person = {
        .amount = 0,
    };

    sqlite_prepare_table(sqlite);

    do
    {
        *amount = sqlite_get_items_amount(sqlite);
        if (*amount <= 0)
            break;

        sql_person.list = (PERSON_T *)malloc(sizeof(PERSON_T) * (*amount));
        if (sql_person.list == NULL)
            break;

        sqlite_database_open(sqlite);

        ret = sqlite3_exec(sqlite->connection, query, select_callback, &sql_person, &error_msg);
        if (ret != SQLITE_OK)
        {
            fprintf(stderr, "SQL list error: %s\n", error_msg);
            sqlite3_free(error_msg);
            break;
        }

        *person_list = sql_person.list;

    } while (false);

    sqlite3_close(sqlite->connection);

    return status;
}
