/*
 * sum of digits in a number
 */

#include <stdio.h>

int get_number();
int get_sum_of_digits(int n);

int main(void){
    int n, digits_sum;
    n = get_number();
    digits_sum = get_sum_of_digits(n);
    printf("sum of digits in %d: %d\n", n, digits_sum);
    return (0);
}

int get_number(){
    int n;
    printf("Enter number: \n");
    scanf("%d", &n);
    return n;
}

int get_sum_of_digits(int n){
    int i, sum = 0;
    while(n != 0){
        sum = sum + (n % 10);
        n = n / 10;
    }
    return sum;
}