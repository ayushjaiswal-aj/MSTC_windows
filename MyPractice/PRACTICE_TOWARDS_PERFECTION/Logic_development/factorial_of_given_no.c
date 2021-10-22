/*
 * factorial of given number
 */

#include <stdio.h>

#define EXIT_SUCCESS 0

typedef int status_t;

int factorial_r(int n);
int factorial(int n);
int get_number();

int main(void){
    int n, fact;
    n = get_number();
    fact = factorial(n);
    printf("factorial of %d using recurrsion: %d\n", n, fact);
    fact = factorial_r(n);
    printf("factorial of %d using loops: %d\n", n, fact);

    return (EXIT_SUCCESS);
}

int get_number(){
    int n;
    printf("enter number: ");
    scanf("%d", &n);
    return n;
}

int factorial(int n){
    int i, fact = 1;
    for(i = n; i > 0; i--){
        fact = fact * i;
    }
    return fact;
}

int factorial_r(int n){
    if(n == 0){
        return 1;
    }
    return n * factorial_r(n - 1);
}