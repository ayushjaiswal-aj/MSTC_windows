#include <iostream>
#include <stdlib.h>
#include <cstdio>

class Date
{
    private:
        int day, month, year;
    public:
        Date(int init_day, int init_month, int init_year)
        {
            day = init_day;
            month = init_month;
            year = init_year;
        }

        Date()
        {
            day = 1;
            month = 1;
            year = 2000;
        }

        Date(Date& other)
        {
            day = other.day;
            month = other.month;
            year = other.year;
        }

        void show(const char *msg)
        {
            if(msg)
                puts(msg);
            printf("%d-%d-%d\n", day, month, year);
        }
};

int main(void)
{
    Date d1(26, 7, 2021);
    d1.show("d1 = ");

    Date d2(d1);
    d2.show("d2 = ");

    Date d3;
    d3.show("d3 = ");

    return (0);
}