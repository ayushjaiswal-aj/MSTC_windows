#include "Date.H"

int main(void)
{
    Date *pDate = new Date(10, 1, 2020);
    pDate->show("pDate after initializing");

    pDate->set_day(12);
    pDate->set_month(10);
    pDate->set_year(2010);
    pDate->show("pDate after first change: ");

    int day = pDate->get_day();
    int month = pDate->get_month();
    int year = pDate->get_year();

    pDate->set_day(day - 1);
    pDate->set_month(month - 1);
    pDate->set_year(year - 1);
    pDate->show("after second changes");

    delete pDate;
    pDate = 0;

    return 0;
}
