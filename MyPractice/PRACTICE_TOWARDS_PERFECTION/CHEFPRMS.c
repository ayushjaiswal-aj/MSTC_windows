/* 
    code chef and semi-primes 
    problem code - CHEFPRMS 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int isPrime(int num){
    if(num <= 1){
        return FALSE;
    }
    int i;
    for(i=2; i<=sqrt(num); i++){
        if(num % i == 0){
            return FALSE;
        }
    }
    return TRUE;
}

int isSemiPrime(int num){
    int i, j;
    int d1, d2;
    for(i=2; i<=sqrt(num); i++){
        d1 = i;
        if(num % d1 == 0){
            d2 = num/d1;
            if(isPrime(d1) && isPrime(d2) && d1 != d2){
                return TRUE;
            }
        }
    }
    return FALSE;
}

int main(void){
    int T;
    int *arrInput = NULL;
    int *arrOutput = NULL;
    int i, j;
    int a, b;
    int flag;

    scanf("%d", &T);
    arrInput = (int *)malloc(sizeof(int) * T);
    arrOutput = (int *)malloc(sizeof(int) * T);

    for(i=0; i<T; i++){
        scanf("%d", (arrInput + i));
    }
    
    for(i=0; i<T; i++){
        flag = 0;
        for(j=0; j <= arrInput[i]; j++){
            a = j;
            b = arrInput[i] - j;
            if(isSemiPrime(a) && isSemiPrime(b)){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    
    return 0;
}