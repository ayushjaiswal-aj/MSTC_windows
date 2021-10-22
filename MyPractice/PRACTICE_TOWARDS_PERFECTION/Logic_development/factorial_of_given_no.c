/*
 * factorial of given number
 */

#include <stdio.h>

#define EXIT_SUCCESS 0

typedef int status_t;

long long int factorial_r(long long int n);
long long int factorial(long long int n);
long long int get_number();

int main(void){
    long long int n, fact;
    n = get_number();
    fact = factorial(n);
    printf("factorial of %lld using recurrsion: %lld\n", n, fact);
    fact = factorial_r(n);
    printf("factorial of %lld using loops: %lld\n", n, fact);

    return (EXIT_SUCCESS);
}

long long int get_number(){
    long long int n;
    printf("enter number: ");
    scanf("%lld", &n);
    return n;
}

long long int factorial(long long int n){
    long long int i, fact = 1;
    for(i = n; i > 0; i--){
        fact = fact * i;
    }
    return fact;
}

long long int factorial_r(long long int n){
    if(n == 0){
        return 1;
    }
    return n * factorial_r(n - 1);
}