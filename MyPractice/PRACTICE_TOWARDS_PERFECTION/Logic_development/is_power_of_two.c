/*
 * checks if number is power of two.
 */

#include <stdio.h>

int is_power_of_two(int num);

int main(void){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    if(is_power_of_two(n) == 1){
        printf("%d is power of two\n", n);
    }
    else {
        printf("%d is not power of two\n", n);
    }
    return 0;
}

int is_power_of_two(int num){
    return !(num & (num - 1));
}