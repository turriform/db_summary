#if !defined(_H_INITIAL_ARGS_H)
#define _H_INITIAL_ARGS_H
#include "framework.h"

typedef struct InitialArgs initial_args_t;

typedef enum DB
{
    DB_sqlite = 0,
    DB_postgres = 1

} db_t;

struct InitialArgs
{

    db_t db;
    char user[BUF_NAME_MAX];
    char pass[BUF_NAME_MAX];
    char dbname[BUF_NAME_MAX];
    char dbtable[BUF_NAME_MAX];
    char dbfield[BUF_NAME_MAX];
    char host[BUF_NAME_MAX];
    char port[BUF_NAME_MAX];
};


const char *initial_args_db_str(db_t db);

void initial_args_print(initial_args_t *init_args);
void initial_args_fill(initial_args_t *init_args, int argc, char *argv[]);

void initial_args_error(initial_args_t *init_args);

#endif // _H_INITIAL_ARGS_H
