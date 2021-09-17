#include <stdio.h>
#include "Date.H"

Date :: Date(int init_day, int init_month, int init_year)
{
    this->day = init_day;
    this->month = init_month;
    this->year = init_year;
}

int Date :: get_month()
{
    return this->month;
}

int Date :: get_day()
{
    return this->day;
}

int Date :: get_year()
{
    return this->year;
}

void Date :: set_day (int new_day)
{
    this->day = new_day;
}

void Date :: set_month(int new_month)
{
    this->month = new_month;
}

void Date :: set_year(int new_year)
{
    this->year = new_year;
}

void Date :: show(const char *msg)
{
    if(msg)
        puts(msg);
    printf("%d-%d-%d\n", this->day, this->month, this->year);
}