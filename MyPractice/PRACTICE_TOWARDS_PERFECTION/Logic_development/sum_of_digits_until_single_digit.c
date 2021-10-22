/*
 * sum of digits of until single digit is obtained
 */

#include <stdio.h>
 
int get_number();
int get_sum(int n);

int main(void){
    int n, sum;
    n = get_number();
    sum = get_sum(n);
    printf("Sum : %d\n", sum);
    return (0);
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

int get_sum(int n){
    int i, sum = n;
    while(sum / 10 != 0){
        n = sum;
        sum = 0;
        while(n != 0){
            sum = sum + (n % 10);
            n = n / 10;
        }
    }
    return sum;
}