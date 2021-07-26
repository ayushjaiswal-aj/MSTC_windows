#include <stdio.h>

class Date
{
    private:
        int day, month, year;
    
    public:
        Date(int dd, int mm, int yy)
        {
            this->day = dd;
            this->month = mm;
            this->year = yy;
        }

        int get_day()
        {
            return this->day;
        }

        int get_month()
        {
            return this->month;
        }

        int get_year()
        {
            return this->year;
        }

        void set_day(int new_day)
        {
            this->day = new_day;
        }

        void set_month(int new_month)
        {
            this->month = new_month;
        }

        void set_year(int new_year)
        {
            this->year = new_year;
        }

        void show(const char *msg)
        {
            if(msg)
                puts(msg);
            
            printf("%d-%d-%d", this->day, this->month, this->year);
        }
};

int main(void)
{
    Date test_d(1, 1, 1970);
    test_d.show("test_d");
    Date* pDate = new Date(21, 1, 2021);
    pDate->show("pDate: ");

    int day = pDate->get_day();
    int month = pDate->get_month();
    int year = pDate->get_year();

    pDate->set_day(17);
    pDate->set_month(10);
    pDate->set_year(2020);

    day = pDate->get_day();
    month = pDate->get_month();
    year = pDate->get_year();

    Date* pBirthDate = new Date(19, 6, 1999);
    pBirthDate->show("pBirthDate:");
    day = pBirthDate->get_day();
    month = pBirthDate->get_month();
    year = pBirthDate->get_year();

    delete pDate;
    pDate = NULL;

    delete pBirthDate;
    pBirthDate = NULL;

    return (0);
}