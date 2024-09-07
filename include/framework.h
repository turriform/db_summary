#if !defined(L_DATABASE_FRAMEWORK_H)
#define L_DATABASE_FRAMEWORK_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <libpq-fe.h>
#include <sqlite3.h>

#include <limits.h>
#include <math.h>


#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)


#define DB_PG_DEFAULT_HOST      "localhost"
#define DB_PG_DEFAULT_PORT      "5432"
#define DB_PG_DEFAULT_USERNAME  "postgres"

#define BUF                     4096U
#define BUF_NAME_MAX            256U
#define BUF_QUERY               BUF

#define STR_N_LEN(str) (const char *)(str), strlen((const char *)(str)) + 1



#endif // L_DATABASE_FRAMEWORK_H
