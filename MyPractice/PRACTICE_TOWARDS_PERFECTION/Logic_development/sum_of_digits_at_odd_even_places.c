/* 
 * calculate the sum of digits at odd and even places
 */

#include <stdio.h>

int get_number();
int get_sum_of_even_places(int n);
int get_sum_of_odd_places(int n);

int main(void){
    int n;
    n = get_number();
    printf("sum of digits at even places: %d\n", get_sum_of_even_places(n));
    printf("sum of digits at odd places: %d\n", get_sum_of_odd_places(n));
    return (0);
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

int get_sum_of_even_places(int n){
    int sum = 0;
    while(n != 0){
        int div = n % 100;
        sum = sum + div/10;
        n = n / 100;
    }
    return sum;
}

int get_sum_of_odd_places(int n){
    int sum = 0;
    while(n != 0){
        int div = n % 100;
        sum = sum + div%10;
        n = n / 100;
    }
    return sum;
}