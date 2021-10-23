/*
 *prints multiples of 3 and 5 till n
 */

#include <stdio.h>

int get_number();
int get_sum_of_multiples_of_3_and_5_till_n(int n);

int main(void){
    int n, sum;
    n = get_number();
    sum = get_sum_of_multiples_of_3_and_5_till_n(n);
    printf("Sum of multiples of 3 and 5 till %d: %d\n", n, sum);
    return 0;
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

int get_sum_of_multiples_of_3_and_5_till_n(int n){
    int i, sum = 0;
    for(i = 1; i < n; i++){
        if(i % 3 == 0 || i % 5 == 0){
            printf("multiple: %d\n", i);
            sum = sum + i;
        }
    }
    return sum;
}