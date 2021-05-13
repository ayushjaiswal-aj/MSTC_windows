#include "DateVector.h"

int main(void){
    int iDate1, iDate2;

    InitDateLib();

    iDate1 = CreateDate(10, 2, 2021);
    iDate2 = CreateDate(2, 3, 1999);

    ShowDate(iDate1);
    ShowDate(iDate2);

    SetDay(iDate1, 19);
    SetMonth(iDate1, 6);
    SetYear(iDate1, 1999);

    ShowDate(iDate1);
    ReleaseDateLib();

    return 0;
}