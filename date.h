#include <stdbool.h>
#ifndef DATEH
#define DATEH

/**
 *
 * Representation of a date. Functions are from a joint exercise in class.
 */

typedef struct
{

    int day;
    int month;
    int year;

} date;

bool set_date(date *a_date, int day, int month, int year);

bool is_valid(date a_date);

bool isLeapYear(date datum);

void print_fi_standard(date a_date);

void print_ISO_standard(date a_date);

bool dates_equal(date datum1, date datum2);

bool is_before(date firstDate, date secondDate);

date get_previous_day(date a_date);

date get_day_after(date a_date);

date get_n_days_previous(date a_date, int days);

void set_to_today(date *a_date);

date dateWhenPositive(void);

void clearBuffer(void);

#endif