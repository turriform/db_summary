#if !defined(LOCAL_POSTGRES_IFACE_H)
#define LOCAL_POSTGRES_IFACE_H
#include "framework.h"
#include "initial_args.h"


enum PG_OID_REPLICA
{ // from     src/interfaces/ecpg/ecpglib/pg_type.h
    BOOLOID = 16,
    BYTEAOID = 17,
    CHAROID = 18,
    NAMEOID = 19,
    INT8OID = 20,
    INT2OID = 21,
    INT2VECTOROID = 22,
    INT4OID = 23,
    REGPROCOID = 24,
    TEXTOID = 25,
    OIDOID = 26,
    TIDOID = 27,
    XIDOID = 28,
    CIDOID = 29,
    OIDVECTOROID = 30,
    POINTOID = 600,
    LSEGOID = 601,
    PATHOID = 602,
    BOXOID = 603,
    POLYGONOID = 604,
    LINEOID = 628,
    FLOAT4OID = 700,
    FLOAT8OID = 701,
    ABSTIMEOID = 702,
    RELTIMEOID = 703,
    TINTERVALOID = 704,
    UNKNOWNOID = 705,
    CIRCLEOID = 718,
    CASHOID = 790,
    INETOID = 869,
    CIDROID = 650,
    BPCHAROID = 1042,
    VARCHAROID = 1043,
    DATEOID = 1082,
    TIMEOID = 1083,
    TIMESTAMPOID = 1114,
    TIMESTAMPTZOID = 1184,
    INTERVALOID = 1186,
    TIMETZOID = 1266,
    ZPBITOID = 1560,
    VARBITOID = 1562,
    NUMERICOID = 1700,
};





void 
postgres_conn_str
(char *buff, const char *host, const char *port, const char *username, const char *password, const char *dbname);

PGconn *
postgres_create_connection(initial_args_t *args);

void 
postgres_close_connection(PGconn *conn);

PGresult *
postgres_get_result_from_query(PGconn *conn, const char *query);

void 
postgres_init(initial_args_t *params);

#endif // LOCAL_POSTGRES_IFACE_H
