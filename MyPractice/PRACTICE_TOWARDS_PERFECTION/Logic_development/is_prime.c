/*
 * checks if the number is prime
 */

#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

int get_number();
bool is_prime(int n);

int main(void){
    int n;
    n = get_number();
    if(is_prime(n)){
        printf("%d is a prime\n", n);
    }
    else{
        printf("%d is not an prime\n", n);
    }

    return (0);
}

int get_number(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    return n;
}

bool is_prime(int n){
    int i;
    for(i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            return FALSE;
        }
    }
    return TRUE;
}