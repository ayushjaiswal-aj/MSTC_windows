#include <cstdio>
#include <iostream>

class Date
{
    private:
        int day, month, year;
    
    public:
        Date(int init_dd, int init_mm, int init_yy)
        {
            day = init_dd;
            month = init_mm;
            year = init_yy;
        }

        Date& operator=(const Date& other)
        {
            this->day = other.day;
            this->month = other.month;
            this->year = other.year;
            return *this;
        }

        void show()
        {
            printf("%d-%d-%d\n", day, month, year);
        }
};

Date& get_date_instance(int, int, int);

int main(void)
{
    int n = 1000;
    int *p = new int(100);

    int& m = *p;
    printf("m = %d\n", m);
    m = 500;
    printf("*p = %d\n", *p);

    m = n;
    printf("m = &n = %d\n", m);

    delete &m;

    Date& ref = get_date_instance(1, 5, 2020);
    ref.show();

    delete &ref;
    return (0);
}

Date& get_date_instance(int d, int m, int y)
{
    Date *pDate = new Date(d, m, y);
    return (*pDate);
}