/*
 *Reversing digits in a number.
 */

#include <stdio.h>
#include <stdlib.h>

int get_digit_count(int num);
int get_reversed_number(int num);

int main(void){
    int num;
    int reversed_num;
    printf("Enter number: ");
    scanf("%d", &num);
    reversed_num = get_reversed_number(num);
    printf("reversed number: %d\n", reversed_num);
    return 0;
}

int get_digit_count(int num){
    int count = 0;
    while(num != 0){
        num = num / 10;
        count ++;
    }
    return count;
}

int get_reversed_number(int num){
    int *digits = NULL;
    int nr_digits = get_digit_count(num);
    int i = 0, place = 1;
    int reversed_number = 0;
    digits = (int *)malloc(sizeof(int) * nr_digits);
    while(num != 0){
        digits[i] = num % 10;
        num = num / 10;
        i ++;
    }
    for(i = nr_digits - 1; i >= 0; i--){
        reversed_number = reversed_number + (digits[i] * place);
        place = place * 10;
    }
    return reversed_number;
}