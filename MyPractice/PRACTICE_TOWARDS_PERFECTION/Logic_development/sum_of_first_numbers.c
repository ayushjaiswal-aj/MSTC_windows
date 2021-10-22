/*
 * Sum of first numhers. (normal, formula)
 */

#include <stdio.h>

#define EXIT_SUCCESS 0

int get_number();
int sum_formula(int n);
int sum_loop(int n);

int main(void){
    int n;
    int sum;

    n = get_number();
    sum = sum_formula(n);
    printf("sum of first %d numbers using formula = %d\n", n, sum);
    sum = sum_loop(n);
    printf("sum of first %d numbers using loops = %d\n", n, sum);

    return (EXIT_SUCCESS);
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

int sum_formula(int n){
    return ((n * (n + 1))/2);
}

int sum_loop(int n){
    int i, sum = 0;
    for(i=0; i<=n; i++){
        sum = sum + i;
    }
    return sum;
}