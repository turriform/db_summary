#include "initial_args.h"

static inline void intial_args_parse(char *dest, const char *src, const char *needle, size_t start_from)
{
    char *str = strstr(src, needle);
    if (str)
    {
        size_t i = 0;
        while (src[i] != '\0')
            dest[i++] = src[start_from++];
    }
}

const char *initial_args_db_str(db_t db)
{
    return db == DB_postgres ? "Postgres" : "SQLite";
}

void initial_args_print(initial_args_t *init_args)
{
    printf(
        "Args\nDatabase\t%s\nUsername:\t%s\nPassword:\t%s\nDB Name\t\t%s\nDB Table\t%s\nDB Field\t%s\n",
        initial_args_db_str(init_args->db),
        (strlen(init_args->user) > 0) ? init_args->user : "N/A",
        (strlen(init_args->pass) > 0) ? "********" : "Not supplied",
        (strlen(init_args->dbname) > 0) ? init_args->dbname : "N/A",
        (strlen(init_args->dbtable) > 0) ? init_args->dbtable : "N/A",
        (strlen(init_args->dbfield) > 0) ? init_args->dbfield : "N/A");
}

void initial_args_fill(initial_args_t *init_args, int argc, char *argv[])
{

    char db[BUF_NAME_MAX] = "";

    for (int i = 1; i != argc; i++)
    {
        intial_args_parse(db, argv[i], "db_type=", strlen("db_type="));
        intial_args_parse(init_args->user, argv[i], "user=", strlen("user="));
        intial_args_parse(init_args->pass, argv[i], "pass=", strlen("pass="));
        intial_args_parse(init_args->dbname, argv[i], "dbname=", strlen("dbname="));
        intial_args_parse(init_args->dbtable, argv[i], "dbtable=", strlen("dbtable="));
        intial_args_parse(init_args->dbfield, argv[i], "dbfield=", strlen("dbfield="));
        intial_args_parse(init_args->host, argv[i], "host=", strlen("host="));
        intial_args_parse(init_args->port, argv[i], "port=", strlen("port="));
    }

    if (strncmp(db, "postgres", strlen("postgres")) == 0)
    {
        init_args->db = DB_postgres;
    }
    if (strncmp(db, "sqlite", strlen("sqlite")) == 0)
    {
        init_args->db = DB_sqlite;
    }
}

void initial_args_error(initial_args_t *init_args)
{
    const char *usage = "";

    if (strlen(init_args->dbname) == 0)
    {
        printf("Database name can't be null \n Usage: %s", usage);
        exit(EXIT_FAILURE);
    }
    if (strlen(init_args->dbfield) == 0)
    {
        printf("Table field can't be null \n Usage: %s", usage);
        exit(EXIT_FAILURE);
    }

    if (strlen(init_args->dbtable) == 0)
    {
        printf("Table can't be null \n Usage: %s", usage);
        exit(EXIT_FAILURE);
    }
}


