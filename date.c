#include "date.h"
#include <stdio.h>
#include <time.h>

bool set_date(date *a_date, int day, int month, int year)
{
    a_date->day = day;
    a_date->month = month;
    a_date->year = year;

    return is_valid(*a_date);
}

bool isLeapYear(date datum)
{
    return datum.year % 4 == 0 && (datum.year % 100 != 0 || datum.year % 400 == 0);
}

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int get_days_per_month(date a_date)
{
    if ((a_date.month == 2) && (isLeapYear(a_date)))
    {

        return 29;
    }
    else
    {
        return daysInMonth[a_date.month];
    }
}

bool is_valid(date a_date)
{

    if (a_date.day > 31 || a_date.day < 1 || a_date.month > 12 ||
        a_date.month < 1)
    {

        return false;
    }

    else
    {

        if ((a_date.month == 2) && isLeapYear(a_date))

        {

            return a_date.day <= 29;
        }
        else

        {

            return a_date.day <= daysInMonth[a_date.month];
        }
    }
}

void print_fi_standard(date a_date)
{

    printf("%d.%d.%d", a_date.day, a_date.month, a_date.year);
}

void print_ISO_standard(date a_date)
{
    printf("%d-%d-%d", a_date.year, a_date.month, a_date.day);
}

bool dates_equal(date datum1, date datum2)
{

    if (datum1.day == datum2.day &&
        datum1.month == datum2.month &&
        datum1.year == datum2.year)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_before(date firstDate, date secondDate)
{

    if (firstDate.year < secondDate.year)
    {

        return true;
    }
    else if (firstDate.year > secondDate.year)
    {

        return false;
    }
    else if (firstDate.month < secondDate.month)
    {

        return true;
    }
    else if (firstDate.month > secondDate.month)
    {

        return false;
    }

    else if (firstDate.day < secondDate.day)
    {
        return true;
    }
    else
    {

        return false;
    }
}

date get_previous_day(date a_date)

{

    if (a_date.day == 1)
    {

        a_date.month = a_date.month - 1;

        if (a_date.month == 0)
        {

            a_date.year = a_date.year - 1;
            a_date.month = 12;
        }

        a_date.day = get_days_per_month(a_date);
    }

    else
    {

        a_date.day = a_date.day - 1;
    }

    return a_date;
}

date get_day_after(date a_date)
{

    if (a_date.day == get_days_per_month(a_date))
    {

        if (a_date.month == 12)
        {

            a_date.year = a_date.year + 1;
            a_date.month = 1;
        }
        else
        {
            a_date.month = a_date.month + 1;
        }

        a_date.day = 1;
    }

    else
    {

        a_date.day = a_date.day + 1;
    }

    return a_date;
}

date get_n_days_previous(date a_date, int days)
{
    date index_date = a_date;

    while (days > 0)
    {

        days--;
        index_date = get_previous_day(index_date);
    }

    return index_date;
}

void set_to_today(date *a_date)
{
    time_t today_in_seconds;
    struct tm *timeinfo;

    today_in_seconds = time(NULL);
    timeinfo = localtime(&today_in_seconds);

    a_date->day = timeinfo->tm_mday;
    a_date->month = timeinfo->tm_mon + 1;
    a_date->year = timeinfo->tm_year + 1900;
}

date dateWhenPositive(void)
{

    printf("Please enter the date when you tested positive: ");
    date datePositive;

    scanf("%d.%d.%d", &datePositive.day, &datePositive.month, &datePositive.year);
    clearBuffer();
    while (!is_valid(datePositive))
    {
        printf("Inavlid date! Please enter again: ");

        scanf("%d.%d.%d", &datePositive.day, &datePositive.month, &datePositive.year);
        clearBuffer();
    }

    return datePositive;
}

void clearBuffer(void)
{
    while (getchar() != '\n')
    {
    }
}