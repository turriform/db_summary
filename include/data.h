#if !defined(_L_DATATYPE_H)
#define _L_DATATYPE_H
#include "framework.h"

typedef struct db_filed_data
{
    size_t filled;
    size_t size;
    double *arr;
} db_field_data_t;

db_field_data_t *db_field_data_init(size_t n);
void db_field_data_add(db_field_data_t *self, double value);
void db_field_data_free(db_field_data_t *self);

void db_field_print(db_field_data_t *self);

void db_get_summary(db_field_data_t *arr);


void sql_q_select_field_from_table(char *buf, const char *field, const char *table);
#endif // _L_DATATYPE_H
