#include "database_sqlite.h"
#include "data.h"
#include "initial_args.h"

sqlite3 *sqlite_open_db(const char *db_file)
{
    sqlite3 *db;
    sqlite3_open(db_file, &db);
    if (db == NULL)
    {
        printf("Failed to open SQLite\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    printf("Successfully opened %s\n", db_file);

    return db;
}

void sqlite_get_database_summary_and_rel(initial_args_t *initial_args)
{
    sqlite3 *db = sqlite_open_db(initial_args->dbname);

    sqlite3_stmt *stmt;

    char q[BUF_QUERY] = "";
    sql_q_select_field_from_table(q, initial_args->dbfield, initial_args->dbtable);

    sqlite3_prepare_v2(db, q, -1, &stmt, NULL);
    size_t rows = 0;

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        switch (sqlite3_column_type(stmt, 0))
        {

        case SQLITE_INTEGER:
            rows++;
            break;
        case SQLITE_FLOAT:
            rows++;
            break;
 

        default:
            printf("Not recording nun numeric\n");
            break;
        }
    }

    sqlite3_reset(stmt);

    db_field_data_t *values = db_field_data_init(rows);

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        double val = 0;
        switch (sqlite3_column_type(stmt, 0))
        {

        case SQLITE_INTEGER:
            val = (double)sqlite3_column_int(stmt, 0);
            db_field_data_add(values, val);
            break;
        case SQLITE_FLOAT:
            val = (double)sqlite3_column_double(stmt, 0);
            db_field_data_add(values, val);
            break;


        default:
            printf("Can't process non numeric value\n");
            break;
        }

        
    }

    db_get_summary(values);

    db_field_data_free(values);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    printf("Shutting down %s\n", initial_args->dbname);
}
