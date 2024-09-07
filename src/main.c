#include "framework.h"
#include "initial_args.h"
#include "database_pg.h"
#include "database_sqlite.h"
#include "data.h"



int main(int argc, char *argv[])
{

    initial_args_t init_args = (initial_args_t){0};
    initial_args_fill(&init_args, argc, argv);
    
    initial_args_print(&init_args);

    initial_args_error(&init_args);

    if (init_args.db == DB_postgres)
    {
         printf("\nPostgres selected... starting\n");


        postgres_init(&init_args);
    }
    else if (init_args.db == DB_sqlite)
    {
        printf("SQLite selected... starting\n");

        sqlite_get_database_summary_and_rel(&init_args);
    }

    return 0;
}