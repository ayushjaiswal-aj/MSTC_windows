/*
 * Find lucky number of person from name.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_lucky_number(const char *name);
int get_digit_sum_till_last_digit(int lucky_number);

int main(void){
    char *name = (char *)malloc(sizeof(char) * 32);
    int lucky_number;
    printf("Enter name: ");
    gets(name);
    lucky_number = get_lucky_number(name);
    printf("Lucky number of %s is %d\n", name, lucky_number);
    return 0;
}

int get_lucky_number(const char *name){
    int lucky_number = 0;
    int i = 0;
    char c = name[i];
    while(name[i] != '\0'){
        lucky_number += c - 'a' + 1;
        i ++;
        c = name[i];
    }
    lucky_number = get_digit_sum_till_last_digit(lucky_number);
    return lucky_number;
}

int get_digit_sum_till_last_digit(int num){
    int sum = 0;
    while(num != 0){
        sum += num % 10;
        num /= 10;
    }
    if(sum > 9){
        sum = get_digit_sum_till_last_digit(sum);
    }
    return sum;
}