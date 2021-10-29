/*
 *To check if year is leap or not
 */

#include <stdio.h>

int is_leap_year(int year);

int main(void){
    int year;
    printf("Enter year: ");
    scanf("%d", &year);
    if(is_leap_year(year)){
        printf("year: %d is leap year\n", year);
    }
    else {
        printf("year: %d is not a leap year\n", year);
    }
    return 0;
}

int is_leap_year(int year){
    if(year % 100 == 0){
        if(year % 400 == 0){
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        if(year % 4 == 0){
            return 1;
        }
        else {
            return 0;
        }
    }
}