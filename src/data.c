#include "data.h"

db_field_data_t *db_field_data_init(size_t n)
{
    db_field_data_t *arr = (db_field_data_t *)malloc(sizeof(db_field_data_t));
    if (!arr)
    {
        printf("Can't allocate arr\n");
        exit(EXIT_FAILURE);
    }

    arr->arr = (double *)calloc(n, sizeof(double));
    if (!arr->arr)
    {
        printf("Can't calloc arr->arr\n");
        exit(EXIT_FAILURE);
    }

    arr->filled = 0;
    arr->size = n;

    return arr;
}

void db_field_data_add(db_field_data_t *self, double value)
{

    self->arr[self->filled] = value;
    self->filled++;
}

void db_field_data_free(db_field_data_t *self)
{
    if (self->arr)
    {
        free(self->arr);
    }
    free(self);
}

void db_field_print(db_field_data_t *self)
{
    for (size_t i = 0; i != self->filled; i++)
    {
        printf("num %ld, val %f\n", i, self->arr[i]);
    }
}

static double db_get_min(db_field_data_t *arr)
{
    double res = (double)LONG_MAX;
    for (size_t i = 0; i != arr->size; i++)
        res = MIN(res, arr->arr[i]);
    return res;
}

static double db_get_max(db_field_data_t *arr)
{
    double res = (double)LONG_MIN;
    for (size_t i = 0; i != arr->size; i++)
        res = MAX(res, arr->arr[i]);
    return res;
}

static double db_get_sum(db_field_data_t *arr)
{
    double res = 0;
    for (size_t i = 0; i != arr->size; i++)
        res += arr->arr[i];
    return res;
}

static double db_get_avg(db_field_data_t *arr)
{
    double sum = db_get_sum(arr);
    if (sum != 0)
        return (double)(sum / arr->size);
    return 0;
}

static double db_get_dis(db_field_data_t *arr)
{

    double avg = db_get_avg(arr);

    double des_sum = 0;
    for (size_t i = 0; i != arr->size; i++)
        des_sum += (pow((arr->arr[i] - avg), 2));

    if (des_sum != 0)
        return (des_sum / arr->size);
    return 0;
}

void db_get_summary(db_field_data_t *arr)
{
    if (arr->size == 0)
    {
        printf("The table was empty\n");
    }

    else
    {
        double avg = db_get_avg(arr),
               min = db_get_min(arr),
               max = db_get_max(arr),
               sum = db_get_sum(arr),
               des = db_get_dis(arr);

        printf("Summary: \nAvg\t\t%.2f\nMin\t\t%.2f\nMax\t\t%.2f\nSum\t\t%.2f\nDispersion\t%.2f\n",
               avg, min, max, sum, des);
    }
}

// query

void sql_q_select_field_from_table(char *buf, const char *field, const char *table)
{

    strncat(buf, "SELECT ", strlen("SELECT ") + 1);
    strncat(buf, field, strlen(field));
    strncat(buf, " FROM ", strlen(" FROM ") + 1);
    strncat(buf, table, strlen(table));
}
