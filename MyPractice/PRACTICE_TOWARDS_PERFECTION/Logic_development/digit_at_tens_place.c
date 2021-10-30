/*
 *returns digits at tens place.
 */

#include <stdio.h>
#include <stdlib.h>

int get_digit_at_tens_place(int num);

int main(void){
    int num;
    int digit_at_tens;
    printf("Enter number: ");
    scanf("%d", &num);

    digit_at_tens = get_digit_at_tens_place(num);
    printf("digit at tens place is %d\n", digit_at_tens);

    return 0;
}

int get_digit_at_tens_place(int num){
    return ((num % 100) / 10);
}