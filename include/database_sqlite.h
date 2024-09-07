#if !defined(_L_SQLITE_H_)
#define _L_SQLITE_H_
#include "framework.h"

#include "initial_args.h"

sqlite3 *sqlite_open_db(const char *db_file);
void sqlite_get_database_summary_and_rel(initial_args_t *initial_args);

#endif // _L_SQLITE_H_
