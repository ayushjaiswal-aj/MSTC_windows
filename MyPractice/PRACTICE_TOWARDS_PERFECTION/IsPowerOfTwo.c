#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;

bool isPowerOfTwo(int n);
bool isPowerOfTwoPro(int n);

int main(void){
    unsigned int n;
    printf("enter number: ");
    scanf("%u", &n);

    printf("using log2(n) function\n");
    if(isPowerOfTwo(n)){
        printf("%d is power of 2\n", n);
    }
    else {
        printf("%d is not a power of 2\n", n);
    }
    
    printf("using and operation\n");
    if(isPowerOfTwoPro(n)){
        printf("%d is power of 2\n", n);
    }
    else {
        printf("%d is not a power of 2\n", n);
    }

    return (EXIT_SUCCESS);
}

bool isPowerOfTwo(int n){
    return (ceil(log2(n)) == floor(log2(n)));
}

bool isPowerOfTwoPro(int n){
    return (!(n & (n - 1)));
}