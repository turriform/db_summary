#include "database_pg.h"
#include "initial_args.h"
#include "data.h"

static void postgres_finish_with_error(PGconn *conn)
{
    puts(PQerrorMessage(conn));
    PQfinish(conn);
    printf("We are leaving...\n");
    exit(EXIT_FAILURE);
}

void postgres_conn_str(char *buff, const char *host, const char *port, const char *username, const char *password, const char *dbname)
{ // host
    strncat(buff, STR_N_LEN("host="));

    if (strlen(host) == 0)
        strncat(buff, STR_N_LEN(DB_PG_DEFAULT_HOST));
    else
        strncat(buff, STR_N_LEN(host));

    strncat(buff, STR_N_LEN(" "));

    // port
    strncat(buff, STR_N_LEN("port="));
    if (strlen(port) == 0)
        strncat(buff, STR_N_LEN(DB_PG_DEFAULT_PORT));
    else
        strncat(buff, STR_N_LEN(port));

    strncat(buff, STR_N_LEN(" "));

    // username
    strncat(buff, STR_N_LEN("user="));
    if (strlen(username) == 0)
        strncat(buff, STR_N_LEN(DB_PG_DEFAULT_USERNAME));
    else
        strncat(buff, STR_N_LEN(username));

    strncat(buff, STR_N_LEN(" "));

    // dbname
    strncat(buff, STR_N_LEN("dbname="));
    strncat(buff, STR_N_LEN(dbname));
    strncat(buff, STR_N_LEN(" "));

    // password
    if (strlen(password) > 0)
    {
        strncat(buff, STR_N_LEN("password="));
        strncat(buff, STR_N_LEN(password));
    }
}

PGconn *
postgres_create_connection(initial_args_t *args)
{
    char conn_str[BUF] = "";
    postgres_conn_str(conn_str, args->host, args->port, args->user, args->pass, args->dbname);

    PGconn *connection =
        PQconnectdb(conn_str);

    if (PQstatus(connection) != CONNECTION_OK)
    {
        postgres_finish_with_error(connection);
        return NULL;
    }
    printf("Connection ok\n");
    return connection;
}

void postgres_close_connection(PGconn *conn)
{
    if (conn)
    {
        PQfinish(conn);
        printf("Connection to postgres db closed \n");
    }
    else
    {
        printf("Connection to postgres was already closed \n");
    }
}



PGresult *postgres_get_result_from_query(PGconn *conn, const char *query)
{
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        postgres_finish_with_error(conn);
    }

    printf("Got results from query: %s", query);
    return res;
}

void postgres_init(initial_args_t *params)
{

    PGconn *conn = postgres_create_connection(params);

    char q[BUF_QUERY] = "";

    sql_q_select_field_from_table(q, params->dbfield, params->dbtable);

    PGresult *res = postgres_get_result_from_query(conn, q);

    int ncols = PQnfields(res);
    for (int i = 0; i < ncols; i++)
    {
        Oid type = PQftype(res, i);

        switch (type)
        {
        case INT2OID:
        case INT4OID:
        case INT8OID:
        {
            printf("\nProcessing numeric values\n");

            int nrows = PQntuples(res);
            db_field_data_t *values = db_field_data_init(nrows);

            for (i = 0; i != nrows; i++)
            {
                char *field = PQgetvalue(res, i, 0);
                db_field_data_add(values, atof(field));
            }

            db_get_summary(values);

            db_field_data_free(values);
            break;
        }

        default:
            printf("Impossable to process non numeric value\n");
        }
    }

    PQclear(res);
    PQfinish(conn);
}
